/**
 * archivo.h
 * 
 * En este archivo se definen las funciones y estructuras necesarias para el manejo, control y operación de distintos
 * tipos de archivos.
 */
#ifndef ARCHIVO_H_INCLUIDO
#define ARCHIVO_H_INCLUIDO

// Cabeceras necesarias.
#include "cliente.h"
#include "proveedor.h"
#include "carrito.h"
#include "libro.h"

// Constantes de operación.
#define RUTA_ARCHIVO_CLIENTES "./data/clientes.data"
#define RUTA_ARCHIVO_PROVEEDORES "./data/proveedores.data"
#define RUTA_ARCHIVO_CARRITOS "./data/carritos.data"
#define RUTA_ARCHIVO_LIBROS "./data/libros.data"
#define LECTURA_ARCHIVO_CLIENTES_EXITO 0
#define LECTURA_ARCHIVO_CLIENTES_ERROR -1
#define LECTURA_ARCHIVO_PROVEEDORES_EXITO 0
#define LECTURA_ARCHIVO_PROVEEDORES_ERROR -1
#define LECTURA_ARCHIVO_CARRITOS_EXITO 0
#define LECTURA_ARCHIVO_CARRITOS_ERROR -1
#define LECTURA_ARCHIVO_LIBROS_EXITO 0
#define LECTURA_ARCHIVO_LIBROS_ERROR -1
#define ESCRITURA_ARCHIVO_CLIENTES_EXITO 0
#define ESCRITURA_ARCHIVO_CLIENTES_ERROR -1
#define ESCRITURA_ARCHIVO_PROVEEDORES_EXITO 0
#define ESCRITURA_ARCHIVO_PROVEEDORES_ERROR -1
#define ESCRITURA_ARCHIVO_CARRITOS_EXITO 0
#define ESCRITURA_ARCHIVO_CARRITOS_ERROR -1
#define ESCRITURA_ARCHIVO_LIBROS_EXITO 0
#define ESCRITURA_ARCHIVO_LIBROS_ERROR -1

// Prototipos de funciones
int leer_clientes_en_memoria(cliente **, size_t *);
int leer_proveedores_en_memoria(proveedor **, size_t *);
int leer_carritos_en_memoria(carrito **, size_t *);
int leer_libros_en_memoria(libro **, size_t *);
int escribir_clientes_en_archivo(cliente *, size_t);
int escribir_proveedores_en_archivo(proveedor *, size_t);
int escribir_carritos_en_archivo(carrito *, size_t);
int escribir_libros_en_archivo(libro *, size_t);

#endif // ARCHIVO_H_INCLUIDO
