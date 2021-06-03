/**
 * control.c
 * 
 * En este archivo se describen las implementaciones de distintas funciones necesarias para el proceso de control
 * de E-Shelf.
 */
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include "control.h"
#include "hilo.h"
#include "memoria_compartida.h"

/**
 * AVISO
 * Esta sección de código contiene variables globales *debido* a que es la forma más fácil para controlar una señal como sigterm,
 * sigint, etc...
 */

// Variable global que indica si nuestro ciclo infinito de espera debe seguir, vaya, esperando.
int bandera_seguir_esperando = 1;

/**
 * control_de_sigterm
 * Función que es llamada en cuanto recibimos un Ctrl+C, con el cual debemos comenzar el protocolo de finalización de ejecución
 * de nuestro proceso de control primario.
 */
void control_de_sigterm()
{
  // Colocamos la bandera en 0
  bandera_seguir_esperando = 0;
}

/**
 * esperar_hastas_sigterm
 * Esta función contiene un ciclo infinito que espera hasta que el usuario presiona Ctrl+C para finalizar la ejecución. Para ello
 * se liga la función control_de_sigterm() como escucha del evento y aquí mantenemos el mencionado ciclo infinito a manera de pausa.
 */
void esperar_hasta_sigterm()
{
  // Asignamos la función para esperar la señal deseada.
  signal(SIGINT, control_de_sigterm);

  // Un ciclo infinito muy elegante.
  while (bandera_seguir_esperando)
    ;
}

/**
 * cargar_datos_en_memoria
 * Función que se encarga de realizar la carga de todos los datos presentes en archivos en la memoria compartida
 * y los disponibiliza para los procesos clientes mediante la invocación a los hilos de ejecución correspondientes.
 * @param clientes Un apuntador al arreglo final con los clientes cargados.
 * @param num_clientes Un apuntador a la variable final con el número de clientes cargados.
 * @param proveedores Un apuntador al arreglo final con los proveedores cargados.
 * @param num_proveedores Un apuntador a la variable final con el número de proveedores cargados.
 * @param libros Un apuntador al arreglo final con los libros cargados.
 * @param num_libros Un apuntador a la variable final con el número de libros cargados.
 * @param carritos Un apuntador al arreglo final con los carritos cargados.
 * @param num_carritos Un apuntador a la variable final con el número de carritos cargados.
 * @return Un entero indicando el resultado de la operación.
 */
int cargar_datos_en_memoria(cliente **clientes, size_t *num_clientes, int *id_memoria_compartida_clientes, proveedor **proveedores, size_t *num_proveedores, int *id_memoria_compartida_proveedores, libro **libros, size_t *num_libros, int *id_memoria_compartida_libros, carrito **carritos, size_t *num_carritos, int *id_memoria_compartida_carritos)
{
  // Variables locales.
  pthread_t hilo_carritos,
      hilo_clientes,
      hilo_proveedores,
      hilo_libros;
  parametros_carga_carritos *parametros_carritos = malloc(sizeof(parametros_carga_carritos));
  parametros_carga_clientes *parametros_clientes = malloc(sizeof(parametros_carga_clientes));
  parametros_carga_proveedores *parametros_proveedores = malloc(sizeof(parametros_carga_proveedores));
  parametros_carga_libros *parametros_libros = malloc(sizeof(parametros_carga_libros));

  // Validación de memoria.
  if (parametros_carritos == NULL || parametros_clientes == NULL || parametros_proveedores == NULL || parametros_libros == NULL)
  {
    // Regresamos el error apropiado.
    return CARGA_DATOS_ERROR;
  }

  // Asignamos nuestros datos.
  parametros_carritos->carritos = carritos;
  parametros_carritos->numero_carritos = num_carritos;
  parametros_carritos->id_memoria_compartida = id_memoria_compartida_carritos;
  parametros_clientes->clientes = clientes;
  parametros_clientes->numero_clientes = num_clientes;
  parametros_clientes->id_memoria_compartida = id_memoria_compartida_clientes;
  parametros_proveedores->proveedores = proveedores;
  parametros_proveedores->numero_proveedores = num_proveedores;
  parametros_proveedores->id_memoria_compartida = id_memoria_compartida_proveedores;
  parametros_libros->libros = libros;
  parametros_libros->numero_libros = num_libros;
  parametros_libros->id_memoria_compartida = id_memoria_compartida_libros;

  // Creamos los hilos para la carga de archivos en memoria compartida.
  pthread_create(&hilo_carritos, NULL, hilo_carga_carritos, (void *)parametros_carritos);
  pthread_create(&hilo_clientes, NULL, hilo_carga_clientes, (void *)parametros_clientes);
  pthread_create(&hilo_proveedores, NULL, hilo_carga_proveedores, (void *)parametros_proveedores);
  pthread_create(&hilo_libros, NULL, hilo_carga_libros, (void *)parametros_libros);

  // Esperamos a que finalicen los hilos.
  pthread_join(hilo_carritos, NULL);
  pthread_join(hilo_clientes, NULL);
  pthread_join(hilo_proveedores, NULL);
  pthread_join(hilo_libros, NULL);

  // Verificamos el estado de cada operación.
  if (parametros_carritos->resultado_operacion == HILO_CARGA_CARRITOS_ERROR || parametros_clientes->resultado_operacion == HILO_CARGA_CLIENTES_ERROR || parametros_proveedores->resultado_operacion == HILO_CARGA_PROVEEDORES_ERROR || parametros_libros->resultado_operacion == HILO_CARGA_LIBROS_ERROR)
  {
    // Regresamos el estado de error.
    return CARGA_DATOS_ERROR;
  }

  // Si llegamos a este punto, la ejecución fue la esperada.
  return CARGA_DATOS_EXITOSA;
}

/**
 * descargar_datos_desde_memoria
 * Función que descarga los datos desde la memoria compartida y elimina dicha memoria.
 * @param clientes Un apuntador al arreglo final con los clientes cargados.
 * @param num_clientes Un apuntador a la variable final con el número de clientes cargados.
 * @param proveedores Un apuntador al arreglo final con los proveedores cargados.
 * @param num_proveedores Un apuntador a la variable final con el número de proveedores cargados.
 * @param libros Un apuntador al arreglo final con los libros cargados.
 * @param num_libros Un apuntador a la variable final con el número de libros cargados.
 * @param carritos Un apuntador al arreglo final con los carritos cargados.
 * @param num_carritos Un apuntador a la variable final con el número de carritos cargados.
 * @return Un entero indicando el resultado de la operación.
 */
int descargar_datos_desde_memoria(cliente **clientes, size_t *num_clientes, int id_memoria_compartida_clientes, proveedor **proveedores, size_t *num_proveedores, int id_memoria_compartida_proveedores, libro **libros, size_t *num_libros, int id_memoria_compartida_libros, carrito **carritos, size_t *num_carritos, int id_memoria_compartida_carritos)
{
  // Variables locales.
  int resultado_operacion;

  // Realizamos la operación para clientes.
  resultado_operacion = descargar_clientes_desde_memoria_compartida(clientes, num_clientes, id_memoria_compartida_clientes);

  // Verificamos el resultado.
  if (resultado_operacion == DESCARGA_CLIENTES_MEMORIA_COMPARTIDA_ERROR)
  {
    // Regresamos el resultado adecuado.
    return DESCARGA_DATOS_ERROR;
  }

  // En este punto la ejecución fue la esperada.
  return DESCARGA_DATOS_EXITOSA;
}
