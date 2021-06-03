/**
 * Control.h
 * En este archivo se encuentran las definiciones de funciones necesarias para el
 * proceso de control primario de E-Shelf.
 */
#ifndef CONTROL_H_INCLUIDO
#define CONTROL_H_INCLUIDO

// Constantes de operación.
#define CARGA_DATOS_EXITOSA 1
#define CARGA_DATOS_ERROR -1
#define DESCARGA_DATOS_EXITOSA 1
#define DESCARGA_DATOS_ERROR -1

// Cabeceras necesarias
#include "cliente.h"
#include "proveedor.h"
#include "libro.h"
#include "carrito.h"

// Prototipos de funciones.
int cargar_datos_en_memoria(cliente **, size_t *, int *, proveedor **, size_t *, int *, libro **, size_t *, int *, carrito **, size_t *, int *);
void esperar_hasta_sigterm();
int descargar_datos_desde_memoria(cliente **, size_t *, int, proveedor **, size_t *, int, libro **, size_t *, int, carrito **, size_t *, int);

#endif // CONTROL_H_INCLUIDO
