/**
 * carrito.h
 * 
 * En este archivo se encuentran las definiciones de funciones y estructuras
 * necesarias para trabajar con carritos en E-Shelf.
 */
#ifndef CARRITO_H_INCLUIDO
#define CARRITO_H_INCLUIDO

// Includes necesarios
#include "libro.h"

// Constantes de operación

// Estructura para el carrito
typedef struct estructura_carrito
{
  int id_cliente;
  char isbn[LONGITUD_MAXIMA_ISBN_LIBRO];
  int cantidad;
} carrito;

// Prototipos de funciones
carrito agregar_al_carrito(int, char *);
carrito buscar_carrito_por_id_cliente(int);

#endif // CARRITO_H_INCLUIDO
