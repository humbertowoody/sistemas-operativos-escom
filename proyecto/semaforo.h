/**
 * semaforo.h
 * 
 * En este archivo se definen las funciones y estructuras necesarias para trabajar con semáforos dentro de E-Shelf
 */
#ifndef SEMAFORO_H_INCLUIDO
#define SEMAFORO_H_INCLUIDO

// Constantes de operación
#define LLAVE_SEMAFORO_CLIENTES "e-shelf-cliente-sem"
#define LLAVE_SEMAFORO_CARRITOS "e-shelf-carrito-sem"
#define LLAVE_SEMAFORO_LIBROS "e-shelf-libros-sem"
#define LLAVE_SEMAFORO_PROVEEDORES "e-shelf-proveedores-sem"

// Prototipos de funciones
int crear_semaforo_clientes();
int incrementar_semaforo_clientes();
int decrementar_semaforo_clientes();
int destruir_semaforo_clientes();

#endif // SEMAFORO_H_INCLUIDO
