/**
 * e_shelf_cliente.c
 * 
 * Este archivo contiene la implementación del proceso principal para el cliente
 * del sistema de venta de libros: "E-Shelf".
 */
#include <stdio.h>         // Para operaciones básicas de entrada y salida.
#include "proveedor.h"     // Para las operaciones de proveedores.
#include "gui_proveedor.h" // Para las interfaces gráficas de usuarios proveedores.

// Función principal
int main(int argc, char *argv[])
{
  // Variables locales.
  char correo_electronico[LONGITUD_MAXIMA_CORREO_ELECTRONICO_PROVEEDOR], // Para almacenar el correo electrónico de inicio de sesión.
      contrasenia[LONGITUD_MAXIMA_CONTRASENIA_PROVEEDOR];                // Para almacenar la contraseña de inicio de sesión.
  proveedor proveedor_actual;                                            // Para almacenar el proveedor si se logra el inicio de sesión.
  int resultado_operacion;

  // Mensaje inicial.
  printf("E-Shelf: Acceso de Proveedores.\n");

  // Obtenemos el correo electrónico del proveedor.
  printf("Introduzca su correo electrónico: ");
  scanf("%s", correo_electronico);

  // Obtenemos la contraseña del proveedor.
  printf("Introduzca su contraseña: ");
  scanf("%s", contrasenia);

  // Intentamos el inicio de sesión.
  resultado_operacion = iniciar_sesion_proveedor(correo_electronico, contrasenia, &proveedor_actual);

  // Verificamos el resultado de la operación.
  if (resultado_operacion == INICIO_DE_SESION_PROVEEDOR_EXITOSO)
  {
    // Mostramos el menú principal del proveedor.
    menu_principal_proveedor(proveedor_actual);
  }
  else
  {
    // Mostramos un mensaje de error.
    printf("¡Oh no!\n");
    printf("No pudimos encontrar un usuario y/o contraseña que coincidiera con los datos proporcionados, revísalos e inténtalo de nuevo.\n");
  }

  // Mostramos mensaje final en cualquier caso.
  printf("\nE-Shelf | Sistemas Operativos ESCOM, 2021\n");

  // Exit status = 0.
  return 0;
}
