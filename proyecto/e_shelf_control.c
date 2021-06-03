/**
 * e_shelf_control.c
 * 
 * En este archivo se describe la función principal de funcionamiento para el proceso
 * de control en E-Shelf.
 */
#include <stdio.h>
#include <ncurses.h>
#include "control.h"

// Función principal.
int main(int argc, char *argv[])
{
  // Variables locales.
  cliente *
      clientes_e_shelf;                  // Para almacenar los clientes en E-Shelf.
  libro *libros_e_shelf;                 // Para almacenar los libros en E-Shelf.
  proveedor *proveedores_e_shelf;        // Para almacenar los proveedores en E-Shelf.
  carrito *carritos_e_shelf;             // Para almacenar los carritos en E-Shelf.
  size_t numero_clientes,                // Para almacenar el número de clientes en E-Shelf.
      numero_libros,                     // Para almacenar el número de libros en E-Shelf.
      numero_proveedores,                // Para almacenar el número de proveedores en E-Shelf.
      numero_carritos;                   // Para almacenar el número de carritos en E-Shelf.
  int resultado_operacion_temporal,      // Para almacenar, temporalmente, el resultado de alguna operación intermedia.
      id_memoria_compartida_clientes,    // Para almacenar el ID de la memoria compartida para los clientes.
      id_memoria_compartida_proveedores, // Para almacenar el ID de la memoria compartida para los proveedores.
      id_memoria_compartida_libros,      // Para almacenar el ID de la memoria compartida de los libros.
      id_memoria_compartida_carritos;    // Para almacenar el ID de la memoria compartida de los carritos.

  // Información inicial
  printf("E-Shelf: Proceso de Control.\n");
  printf("Este proceso carga en memoria compartida la información para que los clientes se conecten e interactúen con el sistema de E-Shelf.\n\n");

  // Mensaje inicial de carga de datos.
  printf("Cargando datos en memoria...\n");

  // Cargamos los datos en memoria compartida y creamos los semáforos apropiados.
  resultado_operacion_temporal = cargar_datos_en_memoria(&clientes_e_shelf, &numero_clientes, &id_memoria_compartida_clientes, &proveedores_e_shelf, &numero_proveedores, &id_memoria_compartida_proveedores, &libros_e_shelf, &numero_libros, &id_memoria_compartida_libros, &carritos_e_shelf, &numero_carritos, &id_memoria_compartida_carritos);

  // Verificamos el resultado de la operación.
  if (resultado_operacion_temporal == CARGA_DATOS_EXITOSA)
  {
    printf("¡Carga de datos exitosa!\n");
    printf("Resúmen de datos cargados:\n");
    printf("\t- Clientes: %zu\n", numero_clientes);
    printf("\t- Proveedores: %zu\n", numero_proveedores);
    printf("\t- Libros: %zu\n", numero_libros);
    printf("\t- Carritos: %zu\n", numero_clientes);
    printf("\n\n");
  }
  else
  {
    printf("Ocurrió un error al cargar los datos. Intenta de nuevo más tarde.\n");
    return -1;
  }

  // Mensajes de espera.
  printf("Los clientes y proveedores podrán acceder al sistema a partir de este momento.\n");
  printf("Presiona Control+C para finalizar el proceso de control...\n");
  printf("...");

  // Esperamos hasta que recibamos un control+c.
  esperar_hasta_sigterm();

  // Mostramos un mensaje.
  printf("\n¡Control+C detectado!\nFinalizando programa...\n");

  // Procedemos a descargar los datos desde la memoria compartida y eliminar dicha memoria.
  resultado_operacion_temporal = descargar_datos_desde_memoria(&clientes_e_shelf, &numero_clientes, id_memoria_compartida_clientes, &proveedores_e_shelf, &numero_proveedores, id_memoria_compartida_proveedores, &libros_e_shelf, &numero_libros, id_memoria_compartida_libros, &carritos_e_shelf, &numero_carritos, id_memoria_compartida_carritos);

  // Verificamos el resultado de la operación.
  if (resultado_operacion_temporal == DESCARGA_DATOS_EXITOSA)
  {
    printf("Se han descargado todos los datos desde la memoria compartida.\n");
    printf("Resúmen de datos finales:\n");
    printf("\t- Clientes: %zu\n", numero_clientes);
    printf("\t- Proveedores: %zu\n", numero_proveedores);
    printf("\t- Libros: %zu\n", numero_libros);
    printf("\t- Carritos: %zu\n", numero_clientes);
    printf("\n\n");
  }
  else
  {
    printf("Ocurrió un error al descargar los datos en la memoria compartida.\n");
    return -1;
  }

  // Mensaje final.
  printf("El proceso de control de E-Shelf se ha cerrado exitosamente, cualquier cliente dejará de funcionar a partir de este momento.\n");
  printf("E-Shelf | Sistemas Operativos ESCOM, 2021\n");

  // Si llegamos a este punto, la ejecución fue normal.
  // Exit status = 0.
  return 0;
}
