/**
 * hilo.c
 * 
 * En este archivo se incluyen las implementaciones de las funciones para el manejo y operación de hilos en
 * E-Shelf.
 */
#include "hilo.h"
#include "archivo.h"
#include "memoria_compartida.h"
#include <stdio.h>

/**
 * hilo_carga_clientes
 * Definición de función para la operación del hilo encargado de cargar los clientes desde un archivo
 * hasta una memoria compartida con otros procesos y asignar un semáforo.
 * @param parametros Una variable tipo (void*) que corresponde a una estructura (parametros_carga_clientes*) con los argumentos de la función.
 * @return void
 */
void *hilo_carga_clientes(void *parametros)
{
  // Variables locales.
  parametros_carga_clientes *parametros_clientes = (parametros_carga_clientes *)parametros;
  int resultado_operaciones;

  // Cargamos los datos desde el archivo.
  resultado_operaciones = leer_clientes_en_memoria(parametros_clientes->clientes, parametros_clientes->numero_clientes);

  // Verificamos que la operación haya sido exitosa.
  if (resultado_operaciones == LECTURA_ARCHIVO_CLIENTES_ERROR)
  {
    // Asignamos el error a la estructura de respuesta.
    parametros_clientes->resultado_operacion = HILO_CARGA_CLIENTES_ERROR;

    // Regresamos la estructura de respuesta con el tipo de dato apropiado.
    return NULL;
  }

  // Cargamos los clientes en la memoria compartida.
  resultado_operaciones = cargar_clientes_en_memoria_compartida(parametros_clientes->clientes, *parametros_clientes->numero_clientes, parametros_clientes->id_memoria_compartida);

  // Verificamos el resultado de la operación.
  if (resultado_operaciones == CARGA_CLIENTES_MEMORIA_COMPARTIDA_ERROR)
  {
    // Asignamos el error a la estructura de respuesta.
    parametros_clientes->resultado_operacion = HILO_CARGA_CLIENTES_ERROR;
  }

  // En este punto, la ejecución del hilo fue exitosa colocamos el resultado apropiado y salimos.
  parametros_clientes->resultado_operacion = HILO_CARGA_CLIENTES_EXITO;
  return NULL;
}

/**
 * hilo_carga_proveedores
 * Definición de función para la operación del hilo encargado de cargar los proveedores desde un archivo
 * hasta una memoria compartida con otros procesos y asignar un semáforo.
 * @param parametros Una variable tipo (void*) que corresponde a una estructura (parametros_carga_proveedores*) con los argumentos de la función.
 * @return void
 */
void *hilo_carga_proveedores(void *parametros)
{
  // Variables locales.
  parametros_carga_proveedores *parametros_proveedores = (parametros_carga_proveedores *)parametros;
  int resultado_operaciones;

  // Cargamos los datos desde el archivo.
  resultado_operaciones = leer_proveedores_en_memoria(parametros_proveedores->proveedores, parametros_proveedores->numero_proveedores);

  // Verificamos que la operación haya sido exitosa.
  if (resultado_operaciones == LECTURA_ARCHIVO_PROVEEDORES_ERROR)
  {
    // Asignamos el error a la estructura de respuesta.
    parametros_proveedores->resultado_operacion = HILO_CARGA_PROVEEDORES_ERROR;

    // Regresamos la estructura de respuesta con el tipo de dato apropiado.
    return NULL;
  }

  // Cargamos los proveedores en la memoria compartida.
  resultado_operaciones = cargar_proveedores_en_memoria_compartida(parametros_proveedores->proveedores, *parametros_proveedores->numero_proveedores, parametros_proveedores->id_memoria_compartida);

  // Verificamos el resultado de la operación.
  if (resultado_operaciones == CARGA_PROVEEDORES_MEMORIA_COMPARTIDA_ERROR)
  {
    // Asignamos el error a la estructura de respuesta.
    parametros_proveedores->resultado_operacion = HILO_CARGA_PROVEEDORES_ERROR;
  }

  // En este punto, la ejecución del hilo fue exitosa colocamos el resultado apropiado y salimos.
  parametros_proveedores->resultado_operacion = HILO_CARGA_PROVEEDORES_EXITO;
  return NULL;
}

/**
 * hilo_carga_carritos
 * Definición de función para la operación del hilo encargado de cargar los carritos desde un archivo
 * hasta una memoria compartida con otros procesos y asignar un semáforo.
 * @param parametros Una variable tipo (void*) que corresponde a una estructura (parametros_carga_carritos*) con los argumentos de la función.
 * @return void
 */
void *hilo_carga_carritos(void *parametros)
{
  // Variables locales.
  parametros_carga_carritos *parametros_carritos = (parametros_carga_carritos *)parametros;
  int resultado_operaciones;

  // Cargamos los datos desde el archivo.
  resultado_operaciones = leer_carritos_en_memoria(parametros_carritos->carritos, parametros_carritos->numero_carritos);

  // Verificamos que la operación haya sido exitosa.
  if (resultado_operaciones == LECTURA_ARCHIVO_CARRITOS_ERROR)
  {
    // Asignamos el error a la estructura de respuesta.
    parametros_carritos->resultado_operacion = HILO_CARGA_CARRITOS_ERROR;

    // Regresamos la estructura de respuesta con el tipo de dato apropiado.
    return NULL;
  }

  // Cargamos los carritos en la memoria compartida.
  resultado_operaciones = cargar_carritos_en_memoria_compartida(parametros_carritos->carritos, *parametros_carritos->numero_carritos, parametros_carritos->id_memoria_compartida);

  // Verificamos el resultado de la operación.
  if (resultado_operaciones == CARGA_CARRITOS_MEMORIA_COMPARTIDA_ERROR)
  {
    // Asignamos el error a la estructura de respuesta.
    parametros_carritos->resultado_operacion = HILO_CARGA_CARRITOS_ERROR;
  }

  // En este punto, la ejecución del hilo fue exitosa colocamos el resultado apropiado y salimos.
  parametros_carritos->resultado_operacion = HILO_CARGA_CARRITOS_EXITO;
  return NULL;
}

/**
 * hilo_carga_libros
 * Definición de función para la operación del hilo encargado de cargar los libros desde un archivo
 * hasta una memoria compartida con otros procesos y asignar un semáforo.
 * @param parametros Una variable tipo (void*) que corresponde a una estructura (parametros_carga_libros*) con los argumentos de la función.
 * @return void
 */
void *hilo_carga_libros(void *parametros)
{
  // Variables locales.
  parametros_carga_libros *parametros_libros = (parametros_carga_libros *)parametros;
  int resultado_operaciones;

  // Cargamos los datos desde el archivo.
  resultado_operaciones = leer_libros_en_memoria(parametros_libros->libros, parametros_libros->numero_libros);

  // Verificamos que la operación haya sido exitosa.
  if (resultado_operaciones == LECTURA_ARCHIVO_LIBROS_ERROR)
  {
    // Asignamos el error a la estructura de respuesta.
    parametros_libros->resultado_operacion = HILO_CARGA_LIBROS_ERROR;

    // Regresamos la estructura de respuesta con el tipo de dato apropiado.
    return NULL;
  }

  // Cargamos los libros en la memoria compartida.
  resultado_operaciones = cargar_libros_en_memoria_compartida(parametros_libros->libros, *parametros_libros->numero_libros, parametros_libros->id_memoria_compartida);

  // Verificamos el resultado de la operación.
  if (resultado_operaciones == CARGA_LIBROS_MEMORIA_COMPARTIDA_ERROR)
  {
    // Asignamos el error a la estructura de respuesta.
    parametros_libros->resultado_operacion = HILO_CARGA_LIBROS_ERROR;
  }

  // En este punto, la ejecución del hilo fue exitosa colocamos el resultado apropiado y salimos.
  parametros_libros->resultado_operacion = HILO_CARGA_LIBROS_EXITO;
  return NULL;
}
