/**
 * archivo.c
 * 
 * En este archivo se implementan las funciones definidas en archivo.h cuyos principales objetivos son el manejo de archivos
 * dentro de E-Shelf.
 */
#include <stdio.h>
#include <stdlib.h>
#include "archivo.h"

/**
 * leer_clientes_en_memoria
 * Lee desde un archivo los clientes ahí existentes y los carga en memoria de forma dinámica.
 * @param clientes_leidos Un apuntador para almacenar los clientes que sean leídos desde el archivo
 * @param numero_clientes Un apuntador para almacenar el número de clientes que fueron leídos desde el archivo.
 * @return Un entero cero si no hubo un error u otro número en otro caso.
 */
int leer_clientes_en_memoria(cliente **clientes_leidos, size_t *numero_clientes)
{
  // Variables locales.
  FILE *archivo_clientes;            // Para operar sobre el archivo.
  cliente cliente_temporal,          // Para almacenar, temporalmente, un cliente.
      *clientes_leidos_temp = NULL;  // Para almacenar, temporalmente, los clientes que vayan siendo leídos.
  size_t numero_clientes_leidos = 0; // Para almacenar el número de clientes leídos.

  // Abrimos el archivo en modo lectura.
  archivo_clientes = fopen(RUTA_ARCHIVO_CLIENTES, "r");

  // Verificamos que se haya podido abrir el archivo correctamente.
  if (archivo_clientes == NULL)
  {
    // Regresamos el error apropiado.
    return LECTURA_ARCHIVO_CLIENTES_ERROR;
  }

  // Leemos todos los datos presentes en el archivo.
  while (fread(&cliente_temporal, sizeof(cliente), 1, archivo_clientes))
  {
    // Aumentamos el tamaño de nuestro arreglo temporal.
    clientes_leidos_temp = realloc(clientes_leidos_temp, sizeof(cliente) * (numero_clientes_leidos + 1));

    // Guardamos el cliente en el arreglo.
    clientes_leidos_temp[numero_clientes_leidos] = cliente_temporal;

    // Aumentamos el valor de nuestro contador.
    numero_clientes_leidos += 1;
  }

  // Asignamos los datos leídos al apuntador proporcionado.
  (*clientes_leidos) = clientes_leidos_temp;
  (*numero_clientes) = numero_clientes_leidos;

  // Cerramos el archivo.
  fclose(archivo_clientes);

  // Regresamos el valor apropiado.
  return LECTURA_ARCHIVO_CLIENTES_EXITO;
}

/**
 * escribir_clientes_en_archivo
 * Función que almacena dentro de una archivo un conjunto de clientes proporcionados
 * mediante los parámetros de la función.
 * @param clientes Un arreglo con los clientes a almacenar en el archivo.
 * @param numero_clientes El número de clientes que contiene el arreglo clientes.
 * @return Un entero cero si no ocurrió un error, otro valor para caso de error.
 */
int escribir_clientes_en_archivo(cliente *clientes, size_t numero_clientes)
{
  // Variables locales.
  FILE *archivo_clientes; // Para operar sobre el archivo de clientes.

  // Abrimos el archivo en modo escritura.
  archivo_clientes = fopen(RUTA_ARCHIVO_CLIENTES, "w");

  // Verificamos que se haya podido abrir el archivo correctamente.
  if (archivo_clientes == NULL)
  {
    // Regresamos el error apropiado.
    return ESCRITURA_ARCHIVO_CLIENTES_ERROR;
  }

  // Escribimos en el archivo.
  fwrite(clientes, sizeof(cliente), numero_clientes, archivo_clientes);

  // Cerramos el archivo.
  fclose(archivo_clientes);

  // Regresamos el valor apropiado.
  return ESCRITURA_ARCHIVO_CLIENTES_EXITO;
}

/**
 * leer_proveedores_en_memoria
 * Lee desde un archivo los proveedores ahí existentes y los carga en memoria de forma dinámica.
 * @param proveedores_leidos Un apuntador para almacenar los proveedores que sean leídos desde el archivo
 * @param numero_proveedores Un apuntador para almacenar el número de proveedores que fueron leídos desde el archivo.
 * @return Un entero cero si no hubo un error u otro número en otro caso.
 */
int leer_proveedores_en_memoria(proveedor **proveedores_leidos, size_t *numero_proveedores)
{
  // Variables locales.
  FILE *archivo_proveedores;            // Para operar sobre el archivo.
  proveedor proveedor_temporal,         // Para almacenar, temporalmente, un proveedor.
      *proveedores_leidos_temp = NULL;  // Para almacenar, temporalmente, los proveedores que vayan siendo leídos.
  size_t numero_proveedores_leidos = 0; // Para almacenar el número de proveedores leídos.

  // Abrimos el archivo en modo lectura.
  archivo_proveedores = fopen(RUTA_ARCHIVO_PROVEEDORES, "r");

  // Verificamos que se haya podido abrir el archivo correctamente.
  if (archivo_proveedores == NULL)
  {
    // Regresamos el error apropiado.
    return LECTURA_ARCHIVO_PROVEEDORES_ERROR;
  }

  // Leemos todos los datos presentes en el archivo.
  while (fread(&proveedor_temporal, sizeof(proveedor), 1, archivo_proveedores))
  {
    // Aumentamos el tamaño de nuestro arreglo temporal.
    proveedores_leidos_temp = realloc(proveedores_leidos_temp, sizeof(proveedor) * (numero_proveedores_leidos + 1));

    // Guardamos el proveedor en el arreglo.
    proveedores_leidos_temp[numero_proveedores_leidos] = proveedor_temporal;

    // Aumentamos el valor de nuestro contador.
    numero_proveedores_leidos += 1;
  }

  // Asignamos los datos leídos al apuntador proporcionado.
  (*proveedores_leidos) = proveedores_leidos_temp;
  (*numero_proveedores) = numero_proveedores_leidos;

  // Cerramos el archivo.
  fclose(archivo_proveedores);

  // Regresamos el valor apropiado.
  return LECTURA_ARCHIVO_PROVEEDORES_EXITO;
}

/**
 * escribir_proveedores_en_archivo
 * Función que almacena dentro de una archivo un conjunto de proveedores proporcionados
 * mediante los parámetros de la función.
 * @param proveedores Un arreglo con los proveedores a almacenar en el archivo.
 * @param numero_proveedores El número de proveedores que contiene el arreglo proveedores.
 * @return Un entero cero si no ocurrió un error, otro valor para caso de error.
 */
int escribir_proveedores_en_archivo(proveedor *proveedores, size_t numero_proveedores)
{
  // Variables locales.
  FILE *archivo_proveedores; // Para operar sobre el archivo de proveedores.

  // Abrimos el archivo en modo escritura.
  archivo_proveedores = fopen(RUTA_ARCHIVO_PROVEEDORES, "w");

  // Verificamos que se haya podido abrir el archivo correctamente.
  if (archivo_proveedores == NULL)
  {
    // Regresamos el error apropiado.
    return ESCRITURA_ARCHIVO_PROVEEDORES_ERROR;
  }

  // Escribimos en el archivo.
  fwrite(proveedores, sizeof(proveedor), numero_proveedores, archivo_proveedores);

  // Cerramos el archivo.
  fclose(archivo_proveedores);

  // Regresamos el valor apropiado.
  return ESCRITURA_ARCHIVO_PROVEEDORES_EXITO;
}

/**
 * leer_carritos_en_memoria
 * Lee desde un archivo los carritos ahí existentes y los carga en memoria de forma dinámica.
 * @param carritos_leidos Un apuntador para almacenar los carritos que sean leídos desde el archivo
 * @param numero_carritos Un apuntador para almacenar el número de carritos que fueron leídos desde el archivo.
 * @return Un entero cero si no hubo un error u otro número en otro caso.
 */
int leer_carritos_en_memoria(carrito **carritos_leidos, size_t *numero_carritos)
{
  // Variables locales.
  FILE *archivo_carritos;            // Para operar sobre el archivo.
  carrito carrito_temporal,          // Para almacenar, temporalmente, un carrito.
      *carritos_leidos_temp = NULL;  // Para almacenar, temporalmente, los carritos que vayan siendo leídos.
  size_t numero_carritos_leidos = 0; // Para almacenar el número de carritos leídos.

  // Abrimos el archivo en modo lectura.
  archivo_carritos = fopen(RUTA_ARCHIVO_CARRITOS, "r");

  // Verificamos que se haya podido abrir el archivo correctamente.
  if (archivo_carritos == NULL)
  {
    // Regresamos el error apropiado.
    return LECTURA_ARCHIVO_CARRITOS_ERROR;
  }

  // Leemos todos los datos presentes en el archivo.
  while (fread(&carrito_temporal, sizeof(carrito), 1, archivo_carritos))
  {
    // Aumentamos el tamaño de nuestro arreglo temporal.
    carritos_leidos_temp = realloc(carritos_leidos_temp, sizeof(carrito) * (numero_carritos_leidos + 1));

    // Guardamos el carrito en el arreglo.
    carritos_leidos_temp[numero_carritos_leidos] = carrito_temporal;

    // Aumentamos el valor de nuestro contador.
    numero_carritos_leidos += 1;
  }

  // Asignamos los datos leídos al apuntador proporcionado.
  (*carritos_leidos) = carritos_leidos_temp;
  (*numero_carritos) = numero_carritos_leidos;

  // Cerramos el archivo.
  fclose(archivo_carritos);

  // Regresamos el valor apropiado.
  return LECTURA_ARCHIVO_CARRITOS_EXITO;
}

/**
 * escribir_carritos_en_archivo
 * Función que almacena dentro de una archivo un conjunto de carritos proporcionados
 * mediante los parámetros de la función.
 * @param carritos Un arreglo con los carritos a almacenar en el archivo.
 * @param numero_carritos El número de carritos que contiene el arreglo carritos.
 * @return Un entero cero si no ocurrió un error, otro valor para caso de error.
 */
int escribir_carritos_en_archivo(carrito *carritos, size_t numero_carritos)
{
  // Variables locales.
  FILE *archivo_carritos; // Para operar sobre el archivo de carritos.

  // Abrimos el archivo en modo escritura.
  archivo_carritos = fopen(RUTA_ARCHIVO_CARRITOS, "w");

  // Verificamos que se haya podido abrir el archivo correctamente.
  if (archivo_carritos == NULL)
  {
    // Regresamos el error apropiado.
    return ESCRITURA_ARCHIVO_CARRITOS_ERROR;
  }

  // Escribimos en el archivo.
  fwrite(carritos, sizeof(carrito), numero_carritos, archivo_carritos);

  // Cerramos el archivo.
  fclose(archivo_carritos);

  // Regresamos el valor apropiado.
  return ESCRITURA_ARCHIVO_CARRITOS_EXITO;
}

/**
 * leer_libros_en_memoria
 * Lee desde un archivo los libros ahí existentes y los carga en memoria de forma dinámica.
 * @param libros_leidos Un apuntador para almacenar los libros que sean leídos desde el archivo
 * @param numero_libros Un apuntador para almacenar el número de libros que fueron leídos desde el archivo.
 * @return Un entero cero si no hubo un error u otro número en otro caso.
 */
int leer_libros_en_memoria(libro **libros_leidos, size_t *numero_libros)
{
  // Variables locales.
  FILE *archivo_libros;            // Para operar sobre el archivo.
  libro libro_temporal,            // Para almacenar, temporalmente, un libro.
      *libros_leidos_temp = NULL;  // Para almacenar, temporalmente, los libros que vayan siendo leídos.
  size_t numero_libros_leidos = 0; // Para almacenar el número de libros leídos.

  // Abrimos el archivo en modo lectura.
  archivo_libros = fopen(RUTA_ARCHIVO_LIBROS, "r");

  // Verificamos que se haya podido abrir el archivo correctamente.
  if (archivo_libros == NULL)
  {
    // Regresamos el error apropiado.
    return LECTURA_ARCHIVO_LIBROS_ERROR;
  }

  // Leemos todos los datos presentes en el archivo.
  while (fread(&libro_temporal, sizeof(libro), 1, archivo_libros))
  {
    // Aumentamos el tamaño de nuestro arreglo temporal.
    libros_leidos_temp = realloc(libros_leidos_temp, sizeof(libro) * (numero_libros_leidos + 1));

    // Guardamos el libro en el arreglo.
    libros_leidos_temp[numero_libros_leidos] = libro_temporal;

    // Aumentamos el valor de nuestro contador.
    numero_libros_leidos += 1;
  }

  // Asignamos los datos leídos al apuntador proporcionado.
  (*libros_leidos) = libros_leidos_temp;
  (*numero_libros) = numero_libros_leidos;

  // Cerramos el archivo.
  fclose(archivo_libros);

  // Regresamos el valor apropiado.
  return LECTURA_ARCHIVO_LIBROS_EXITO;
}

/**
 * escribir_libros_en_archivo
 * Función que almacena dentro de una archivo un conjunto de libros proporcionados
 * mediante los parámetros de la función.
 * @param libros Un arreglo con los libros a almacenar en el archivo.
 * @param numero_libros El número de libros que contiene el arreglo libros.
 * @return Un entero cero si no ocurrió un error, otro valor para caso de error.
 */
int escribir_libros_en_archivo(libro *libros, size_t numero_libros)
{
  // Variables locales.
  FILE *archivo_libros; // Para operar sobre el archivo de libros.

  // Abrimos el archivo en modo escritura.
  archivo_libros = fopen(RUTA_ARCHIVO_LIBROS, "w");

  // Verificamos que se haya podido abrir el archivo correctamente.
  if (archivo_libros == NULL)
  {
    // Regresamos el error apropiado.
    return ESCRITURA_ARCHIVO_LIBROS_ERROR;
  }

  // Escribimos en el archivo.
  fwrite(libros, sizeof(libro), numero_libros, archivo_libros);

  // Cerramos el archivo.
  fclose(archivo_libros);

  // Regresamos el valor apropiado.
  return ESCRITURA_ARCHIVO_LIBROS_EXITO;
}
