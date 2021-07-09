/**
 * gui_proveedor.c
 * 
 * En este archivo se implementan las distintas funcionalidades requeridas para la interfaz
 * gráfica de usuario de proveedores en E-Shelf.
 */
#include "gui_proveedor.h"
#include "gui.h"

/**
 * menu_principal_proveedor
 * Muestra el menú principal para proveedores en E-Shelf.
 * @param proveedor_autenticado El proveedor que ha iniciado sesión en el sistema.
 * @return void
 */
void menu_principal_proveedor(proveedor proveedor_autenticado)
{
  // Variables locales.
  int max_filas,    // Para almacenar el número de filas en pantalla.
      max_columnas, // Para almacenar el número de columnas en pantalla.
      opcion_menu;  // Para almacenar la opción seleccionada por el usuario en el menú.

  // Inicialización de nuestro ambiente de texto gráfico.
  if (inicializar_pantalla() == INICIALIZAR_PANTALLA_ERROR)
  {
    printf("Ocurrió un error iniciando el ambiente gráfico, intente de nuevo más tarde.\n");
    return;
  }

  // Obtenemos las dimensiones de la pantalla.
  getmaxyx(stdscr, max_filas, max_columnas);

  // Finalización del ambiente de texto gráfico.
  clear();
  endwin();
}
