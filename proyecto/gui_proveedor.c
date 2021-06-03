/**
 * gui_proveedor.c
 * 
 * En este archivo se implementan las distintas funcionalidades requeridas para la interfaz
 * gráfica de usuario de proveedores en E-Shelf.
 */
#include <ncurses.h>
#include <locale.h>
#include "gui_proveedor.h"

/**
 * menu_principal_proveedor
 * Muestra el menú principal para proveedores en E-Shelf.
 * @param proveedor_autenticado El proveedor que ha iniciado sesión en el sistema.
 * @return void
 */
void menu_principal_proveedor(proveedor proveedor_autenticado)
{
  // Variables locales.
  int max_filas;
  // Inicialización de nuestro ambiente de texto gráfico.
  setlocale(LC_ALL, "es_MX"); // Colocamos la localización en español México.
  initscr();                  // Iniciamos el modo gráfico.
  cbreak();                   // Queremos capturar _todas_ las teclas que presione el usuario (esto incluye Control + C ¡aguas!)
  keypad(stdscr, TRUE);       // Activamos el modo "keypad" para poder utilizar flechas del teclado y demás monerías.
  noecho();                   // No queremos que las teclas que presione el usuario se impriman.

  // Finalización del ambiente de texto gráfico.
  clear();
  endwin();
}
