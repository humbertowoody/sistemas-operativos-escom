/**
 * proveedor.h
 * 
 * En este archivo se definen las funciones y estructuras necesarias para trabajar con proveedores en
 * E-Shelf.
 */
#ifndef PROVEEDOR_H_INCLUIDO
#define PROVEEDOR_H_INCLUIDO

// Constantes de operación.
#define LONGITUD_MAXIMA_NOMBRE_PROVEEDOR 64
#define EDAD_MINIMA_CLIENTE 18
#define LONGITUD_MAXIMA_CONTRASENIA_PROVEEDOR 64
#define LONGITUD_MAXIMA_CORREO_ELECTRONICO_PROVEEDOR 128
#define INICIO_DE_SESION_PROVEEDOR_EXITOSO 0
#define INICIO_DE_SESION_PROVEEDOR_INVALIDO -1

// Estructura que define un proveedor de E-Shelf.
typedef struct estructura_proveedor
{
  int id;
  char correo_electronico[LONGITUD_MAXIMA_CORREO_ELECTRONICO_PROVEEDOR];
  char nombre[LONGITUD_MAXIMA_NOMBRE_PROVEEDOR];
  char contrasenia[LONGITUD_MAXIMA_CONTRASENIA_PROVEEDOR];
} proveedor;

// Prototipos de funciones.
int iniciar_sesion_proveedor(char *, char *, proveedor *);

#endif // PROVEEDOR_H_INCLUIDO
