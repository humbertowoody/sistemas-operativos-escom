/**
 * memoria_compartida.c
 * 
 * En este archivo se incluyen las implementaciones para las operaciones con memoria
 * compartida de E-Shelf.
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "memoria_compartida.h"

/**
 * cargar_clientes_en_memoria_compartida
 * Función que carga un arreglo de clientes dentro de un espacio de memoria compartida y la vuelve
 * disponible para otros procesos.
 * @param clientes Los clientes a almacenar en la memoria compartida
 * @param numero_clientes El número de clientes a almacenar en la memoria compartida
 * @param id_memoria_compartida Un apuntador para almacenar el ID de la memoria compartida.
 * @return Un entero indicando el resultado de la operación.
 */
int cargar_clientes_en_memoria_compartida(cliente **clientes, size_t numero_clientes, int *id_memoria_compartida)
{
  // Variables locales.
  key_t llave_memoria_compartida;
  cliente *clientes_temporal;

  // Creamos la llave para la memoria compartida.
  llave_memoria_compartida = ftok(LLAVE_MEMORIA_COMPARTIDA_CLIENTES, ID_PROYECTO);

  // Creamos la memoria compartida con el doble del tamaño actual (por si se requiere) y obtenemos su id correspondiente.
  (*id_memoria_compartida) = shmget(llave_memoria_compartida, sizeof(cliente) * (numero_clientes + 1) * 2, 0666 | IPC_CREAT);

  // Validamos que se haya creado la memoria compartida.
  if ((*id_memoria_compartida) < 0)
  {
    // Regresamos el resultado de la operación apropiadamente.
    return CARGA_CLIENTES_MEMORIA_COMPARTIDA_ERROR;
  }

  // Nos adjuntamos a la memoria compartida.
  clientes_temporal = (cliente *)shmat((*id_memoria_compartida), 0, 0);

  // Copiamos los contenidos de nuestros clientes anteriores a la memoria compartida.
  for (size_t iterador = 0; iterador < numero_clientes; iterador++)
  {
    clientes_temporal[iterador] = (*clientes)[iterador];
  }

  // Limpiamos el búffer anterior.
  free(*clientes);

  // Asignamos nuestros clientes temporal, la memoria compartida, como valor al apuntador.
  (*clientes) = clientes_temporal;

  // En este punto, la operación fue exitosa así que regresamos el estado apropiado.
  return CARGA_CLIENTES_MEMORIA_COMPARTIDA_EXITO;
}

/**
 * cargar_carritos_en_memoria_compartida
 * Función que carga un arreglo de carritos dentro de un espacio de memoria compartida y la vuelve
 * disponible para otros procesos.
 * @param carritos Los carritos a almacenar en la memoria compartida
 * @param numero_carritos El número de carritos a almacenar en la memoria compartida
 * @param id_memoria_compartida Un apuntador para almacenar el ID de la memoria compartida.
 * @return Un entero indicando el resultado de la operación.
 */
int cargar_carritos_en_memoria_compartida(carrito **carritos, size_t numero_carritos, int *id_memoria_compartida)
{
  // Variables locales.
  key_t llave_memoria_compartida;
  carrito *carritos_temporal;

  // Creamos la llave para la memoria compartida.
  llave_memoria_compartida = ftok(LLAVE_MEMORIA_COMPARTIDA_CARRITOS, ID_PROYECTO);

  // Creamos la memoria compartida con el doble del tamaño actual (por si se requiere) y obtenemos su id correspondiente.
  (*id_memoria_compartida) = shmget(llave_memoria_compartida, sizeof(carrito) * (numero_carritos + 1) * 2, 0666 | IPC_CREAT);

  // Validamos que se haya creado la memoria compartida.
  if ((*id_memoria_compartida) < 0)
  {
    // Regresamos el resultado de la operación apropiadamente.
    return CARGA_CARRITOS_MEMORIA_COMPARTIDA_ERROR;
  }

  // Nos adjuntamos a la memoria compartida.
  carritos_temporal = (carrito *)shmat((*id_memoria_compartida), 0, 0);

  // Copiamos los contenidos de nuestros carritos anteriores a la memoria compartida.
  for (size_t iterador = 0; iterador < numero_carritos; iterador++)
  {
    carritos_temporal[iterador] = (*carritos)[iterador];
  }

  // Limpiamos el búffer anterior.
  free(*carritos);

  // Asignamos nuestros carritos temporal, la memoria compartida, como valor al apuntador.
  (*carritos) = carritos_temporal;

  // En este punto, la operación fue exitosa así que regresamos el estado apropiado.
  return CARGA_CARRITOS_MEMORIA_COMPARTIDA_EXITO;
}

/**
 * cargar_proveedores_en_memoria_compartida
 * Función que carga un arreglo de proveedores dentro de un espacio de memoria compartida y la vuelve
 * disponible para otros procesos.
 * @param proveedores Los proveedores a almacenar en la memoria compartida
 * @param numero_proveedores El número de proveedores a almacenar en la memoria compartida
 * @param id_memoria_compartida Un apuntador para almacenar el ID de la memoria compartida.
 * @return Un entero indicando el resultado de la operación.
 */
int cargar_proveedores_en_memoria_compartida(proveedor **proveedores, size_t numero_proveedores, int *id_memoria_compartida)
{
  // Variables locales.
  key_t llave_memoria_compartida;
  proveedor *proveedores_temporal;

  // Creamos la llave para la memoria compartida.
  llave_memoria_compartida = ftok(LLAVE_MEMORIA_COMPARTIDA_PROVEEDORES, ID_PROYECTO);

  // Creamos la memoria compartida con el doble del tamaño actual (por si se requiere) y obtenemos su id correspondiente.
  (*id_memoria_compartida) = shmget(llave_memoria_compartida, sizeof(proveedor) * (numero_proveedores + 1) * 2, 0666 | IPC_CREAT);

  // Validamos que se haya creado la memoria compartida.
  if ((*id_memoria_compartida) < 0)
  {
    // Regresamos el resultado de la operación apropiadamente.
    return CARGA_PROVEEDORES_MEMORIA_COMPARTIDA_ERROR;
  }

  // Nos adjuntamos a la memoria compartida.
  proveedores_temporal = (proveedor *)shmat((*id_memoria_compartida), 0, 0);

  // Copiamos los contenidos de nuestros proveedores anteriores a la memoria compartida.
  for (size_t iterador = 0; iterador < numero_proveedores; iterador++)
  {
    proveedores_temporal[iterador] = (*proveedores)[iterador];
  }

  // Limpiamos el búffer anterior.
  free(*proveedores);

  // Asignamos nuestros proveedores temporal, la memoria compartida, como valor al apuntador.
  (*proveedores) = proveedores_temporal;

  // En este punto, la operación fue exitosa así que regresamos el estado apropiado.
  return CARGA_PROVEEDORES_MEMORIA_COMPARTIDA_EXITO;
}

/**
 * cargar_libros_en_memoria_compartida
 * Función que carga un arreglo de libros dentro de un espacio de memoria compartida y la vuelve
 * disponible para otros procesos.
 * @param libros Los libros a almacenar en la memoria compartida
 * @param numero_libros El número de libros a almacenar en la memoria compartida
 * @param id_memoria_compartida Un apuntador para almacenar el ID de la memoria compartida.
 * @return Un entero indicando el resultado de la operación.
 */
int cargar_libros_en_memoria_compartida(libro **libros, size_t numero_libros, int *id_memoria_compartida)
{
  // Variables locales.
  key_t llave_memoria_compartida;
  libro *libros_temporal;

  // Creamos la llave para la memoria compartida.
  llave_memoria_compartida = ftok(LLAVE_MEMORIA_COMPARTIDA_LIBROS, ID_PROYECTO);

  // Creamos la memoria compartida con el doble del tamaño actual (por si se requiere) y obtenemos su id correspondiente.
  (*id_memoria_compartida) = shmget(llave_memoria_compartida, sizeof(libro) * (numero_libros + 1) * 2, 0666 | IPC_CREAT);

  // Validamos que se haya creado la memoria compartida.
  if ((*id_memoria_compartida) < 0)
  {
    // Regresamos el resultado de la operación apropiadamente.
    return CARGA_LIBROS_MEMORIA_COMPARTIDA_ERROR;
  }

  // Nos adjuntamos a la memoria compartida.
  libros_temporal = (libro *)shmat((*id_memoria_compartida), 0, 0);

  // Copiamos los contenidos de nuestros libros anteriores a la memoria compartida.
  for (size_t iterador = 0; iterador < numero_libros; iterador++)
  {
    libros_temporal[iterador] = (*libros)[iterador];
  }

  // Limpiamos el búffer anterior.
  free(*libros);

  // Asignamos nuestros libros temporal, la memoria compartida, como valor al apuntador.
  (*libros) = libros_temporal;

  // En este punto, la operación fue exitosa así que regresamos el estado apropiado.
  return CARGA_LIBROS_MEMORIA_COMPARTIDA_EXITO;
}

/**
 * descargar_clientes_desde_memoria_compartida
 * Función que descarga todos los clientes presentes en la memoria compartida a la memoria local
 * y la elimina.
 * @param clientes Un apuntador al arreglo dónde se encuentra, de forma compartida, la memoria y se desea convertir en memoria local.
 * @param numero_clientes Un valor con el número de clientes en la memoria.
 * @param id_memoria_compartida El ID de la memoria compartida para leer y eliminar.
 * @return Un entero indicando el resultado de la operación.
 */
int descargar_clientes_desde_memoria_compartida(cliente **clientes, size_t *numero_clientes, int id_memoria_compartida)
{
  // Variables locales.
  cliente *clientes_temporal;
  size_t numero_clientes_temporal;

  // Calculamos el número de clientes dentro de la memoria compartida.
  for (numero_clientes_temporal = 0; numero_clientes_temporal < (((*numero_clientes) + 1) * 2); numero_clientes_temporal++)
  {
    // No hay id 0.
    if ((*clientes)[numero_clientes_temporal].id <= 0)
    {
      break;
    }
  }

  // Creamos un arreglo temporal del tamaño actual de clientes.
  clientes_temporal = malloc(sizeof(cliente) * numero_clientes_temporal);

  // Verificamos que se haya asignado la memoria correctamente.
  if (clientes_temporal == NULL)
  {
    // Regresamos el mensaje apropiado.
    return DESCARGA_CLIENTES_MEMORIA_COMPARTIDA_ERROR;
  }

  // Copiamos el arreglo en memoria compartida al temporal.
  for (size_t iterador = 0; iterador < numero_clientes_temporal; iterador++)
  {
    clientes_temporal[iterador] = (*clientes)[iterador];
  }

  // Nos desadjuntamos de la memoria compartida.
  shmdt(*clientes);

  // Eliminamos la memoria compartida.
  shmctl(id_memoria_compartida, IPC_RMID, NULL);

  // Asignamos nuestros clientes a nuestra memoria local.
  (*clientes) = clientes_temporal;

  // Asignamos el número de clientes presentes en la memoria compartida como el nuevo número de clientes en la memoria local.
  (*numero_clientes) = numero_clientes_temporal;

  // En este punto la operación fue exitosa.
  return DESCARGA_CLIENTES_MEMORIA_COMPARTIDA_EXITO;
}
