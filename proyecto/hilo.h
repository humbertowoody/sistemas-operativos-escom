/**
 * hilo.h
 * 
 * Este archivo contiene las definiciones de funciones y estructuras necesarias para el manejo
 * de distintos hilos en E-Shelf.
 */
#ifndef HILO_H_INCLUIDO
#define HILO_H_INCLUIDO

// Cabeceras necesarias
#include <stdlib.h>
#include "cliente.h"
#include "carrito.h"
#include "proveedor.h"
#include "libro.h"

// Constantes de operación
#define HILO_CARGA_CLIENTES_EXITO 0
#define HILO_CARGA_CLIENTES_ERROR -1
#define HILO_CARGA_PROVEEDORES_EXITO 0
#define HILO_CARGA_PROVEEDORES_ERROR -1
#define HILO_CARGA_CARRITOS_EXITO 0
#define HILO_CARGA_CARRITOS_ERROR -1
#define HILO_CARGA_LIBROS_EXITO 0
#define HILO_CARGA_LIBROS_ERROR -1

// Estructura para almacenar los parámetros enviados al hilo para carga de clientes.
typedef struct estructura_parametros_carga_clientes
{
  int resultado_operacion;
  size_t *numero_clientes;
  cliente **clientes;
  int *id_memoria_compartida;
} parametros_carga_clientes;

// Estructura para almacenar los parámetros enviados al hilo para carga de proveedores.
typedef struct estructura_parametros_carga_proveedores
{
  int resultado_operacion;
  size_t *numero_proveedores;
  proveedor **proveedores;
  int *id_memoria_compartida;
} parametros_carga_proveedores;

// Estructura para almacenar los parámetros enviados al hilo para carga de carritos.
typedef struct estructura_parametros_carga_carritos
{
  int resultado_operacion;
  size_t *numero_carritos;
  carrito **carritos;
  int *id_memoria_compartida;
} parametros_carga_carritos;

// Estructura para almacenar los parámetros enviados al hilo para carga de libros.
typedef struct estructura_parametros_carga_libros
{
  int resultado_operacion;
  size_t *numero_libros;
  libro **libros;
  int *id_memoria_compartida;
} parametros_carga_libros;

// Prototipos de funciones.
void *hilo_carga_clientes(void *);
void *hilo_carga_proveedores(void *);
void *hilo_carga_carritos(void *);
void *hilo_carga_libros(void *);
void *hilo_guardar_clientes(void *);
void *hilo_guardar_proveedores(void *);
void *hilo_guardar_carritos(void *);
void *hilo_guardar_libros(void *);

#endif // HILO_H_INCLUIDO
