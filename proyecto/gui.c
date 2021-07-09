/**
 * gui.c
 * 
 * En este archivo se implementan las funcionalidades generales de interfaz gráfica de usuario
 * (GUI) para E-Shelf.
 */
#include <ncurses.h>
#include <locale.h>
#include "gui.h"

/**
 * inicializar_pantalla
 * Inicializa la pantalla en modo gráfico con ncurses.
 * @return Un entero indicando el resultado de la operación correspondiente a las banderas.
 */
int inicializar_pantalla()
{
  // Colocamos la localización de la terminal en Español - México
  setlocale(LC_ALL, "es_MX");

  // Iniciamos el modo "gráfico".
  initscr();

  // Capturamos todas las teclas.
  cbreak();

  // Activamos las teclas del teclado.
  keypad(stdscr, TRUE);

  // No queremos imprimir las teclas que presione el usuario.
  noecho();

  // En este punto, la inicialización de la pantalla fue exitosa.
  return INICIALIZAR_PANTALLA_EXITO;
}

/**
 * finalizar_pantalla
 * Finaliza la pantalla en modo gráfico.
 * @return Un entero indicando el resultado de la operación correspondiente a las banderas.
 */
int finalizar_pantalla()
{
  // Limpiamos la pantalla.
  clear();

  // Finalizamos la "ventana".
  endwin();
}

/**
 * obtener_filas_pantalla
 * Regresa el número de filas presentes en la pantalla actual.
 * @return Un entero indicando el número de filas en la pantalla.
 */
int obtener_filas_pantalla()
{
  // Regresamos el valor de la función de ncurses.
  return getmaxy(stdscr);
}

/**
 * obtener_columnas_pantalla
 * Regresa el número de columnas presentes en la pantalla actual.
 * @return Un entero indicando el número de columnas en la pantalla.
 */
int obtener_columnas_pantalla()
{
  // Regresamos el valor de la función de ncurses.
  return getmaxx(stdscr);
}
