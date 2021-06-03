/**
 * memoria_compartida.h
 * 
 * En este archivo se definen las funciones y estructuras necesarias para trabajar con memoria compartida en E-Shelf.
 */
#ifndef MEMORIA_COMPARTIDA_H_INCLUIDO
#define MEMORIA_COMPARTIDA_H_INCLUIDO

// Constantes de operación
#define LLAVE_MEMORIA_COMPARTIDA_CLIENTES "e-shelf-cliente-shm"
#define LLAVE_MEMORIA_COMPARTIDA_CARRITOS "e-shelf-carrito-shm"
#define LLAVE_MEMORIA_COMPARTIDA_LIBROS "e-shelf-libros-shm"
#define LLAVE_MEMORIA_COMPARTIDA_PROVEEDORES "e-shelf-proveedores-shm"
#define CARGA_CLIENTES_MEMORIA_COMPARTIDA_EXITO 0
#define CARGA_CLIENTES_MEMORIA_COMPARTIDA_ERROR -1
#define CARGA_CARRITOS_MEMORIA_COMPARTIDA_EXITO 0
#define CARGA_CARRITOS_MEMORIA_COMPARTIDA_ERROR -1
#define CARGA_PROVEEDORES_MEMORIA_COMPARTIDA_EXITO 0
#define CARGA_PROVEEDORES_MEMORIA_COMPARTIDA_ERROR -1
#define CARGA_LIBROS_MEMORIA_COMPARTIDA_EXITO 0
#define CARGA_LIBROS_MEMORIA_COMPARTIDA_ERROR -1
#define DESCARGA_CLIENTES_MEMORIA_COMPARTIDA_EXITO 0
#define DESCARGA_CLIENTES_MEMORIA_COMPARTIDA_ERROR -1
#define DESCARGA_CARRITOS_MEMORIA_COMPARTIDA_EXITO 0
#define DESCARGA_CARRITOS_MEMORIA_COMPARTIDA_ERROR -1
#define DESCARGA_PROVEEDORES_MEMORIA_COMPARTIDA_EXITO 0
#define DESCARGA_PROVEEDORES_MEMORIA_COMPARTIDA_ERROR -1
#define DESCARGA_LIBROS_MEMORIA_COMPARTIDA_EXITO 0
#define DESCARGA_LIBROS_MEMORIA_COMPARTIDA_ERROR -1
#define ID_PROYECTO 7 // ¡El número de la suerte!

// Cabeceras necesarias
#include <stdlib.h>
#include "cliente.h"
#include "carrito.h"
#include "proveedor.h"
#include "libro.h"

// Prototipos de funciones
int cargar_clientes_en_memoria_compartida(cliente **, size_t, int *);
int cargar_carritos_en_memoria_compartida(carrito **, size_t, int *);
int cargar_proveedores_en_memoria_compartida(proveedor **, size_t, int *);
int cargar_libros_en_memoria_compartida(libro **, size_t, int *);
int descargar_clientes_desde_memoria_compartida(cliente **, size_t *, int);
int descargar_carritos_desde_memoria_compartida(carrito **, size_t *, int);
int descargar_proveedores_desde_memoria_compartida(proveedor **, size_t *, int);
int descargar_libros_desde_memoria_compartida(libro **, size_t *, int);

#endif // MEMORIA_COMPARTIDA_H_INCLUIDO
