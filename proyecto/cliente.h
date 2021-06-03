/**
 * cliente.h
 * 
 * En este archivo se define la cabecera para las operaciones con clientes.
 */
#ifndef CLIENTE_H_INCLUIDO
#define CLIENTE_H_INCLUIDO

// Constantes de operación.
#define LONGITUD_MAXIMA_NOMBRES_CLIENTE 64
#define LONGITUD_MAXIMA_APELLIDO_P_CLIENTE 64
#define LONGITUD_MAXIMA_APELLIDO_M_CLIENTE 64
#define EDAD_MINIMA_CLIENTE 18
#define LONGITUD_MAXIMA_CONTRASENIA_CLIENTE 64
#define LONGITUD_MAXIMA_CORREO_ELECTRONICO_CLIENTE 128

// Estructura para representar un cliente del sistema.
typedef struct estructura_cliente
{
  int id;
  char correo_electronico[LONGITUD_MAXIMA_CORREO_ELECTRONICO_CLIENTE];
  char nombres[LONGITUD_MAXIMA_NOMBRES_CLIENTE];
  char apellido_p[LONGITUD_MAXIMA_APELLIDO_P_CLIENTE];
  char apellido_m[LONGITUD_MAXIMA_APELLIDO_M_CLIENTE];
  int edad;
  char contrasenia[LONGITUD_MAXIMA_CONTRASENIA_CLIENTE];
} cliente;

// Prototipos de funciones.
cliente crear_cliente(int, char *, char *, char *, char *, int, char *);
int agregar_cliente(cliente);
cliente buscar_cliente_por_id(int);
cliente iniciar_sesion(char *, char *);

#endif
