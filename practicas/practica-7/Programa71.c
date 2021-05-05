#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

// Definición de constantes de operación.
#define CARACTER_MURO '#'
#define CARACTER_VACIO ' '
#define CARACTER_JUGADOR '@'
#define CARACTER_META 'F'
#define DIRECCION_ARRIBA 0
#define DIRECCION_IZQUIERDA 1
#define DIRECCION_DERECHA 2
#define DIRECCION_ABAJO 3
#define OPCION_SALIR_MAY 'S'
#define OPCION_SALIR_MIN 's'

// Enumeración para el contenido de cada celda.
enum contenido_celda
{
  MURO,
  VACIO,
  JUGADOR,
  META
};

// Estructura para representar las celdas del mapa.
typedef struct celda
{
  int fila;                     // Coordenada Y
  int columna;                  // Coordenada X
  enum contenido_celda espacio; // El contenido de la celda
} Celda;

// Prototipos de funciones.
void imprimir_mapa(WINDOW *ventana_laberinto, int filas, int columnas, Celda **mapa);
void busqueda_en_profundidad(int fila_actual, int columna_actual, int filas, int columnas, Celda **mapa);
void obtener_direcciones_disponibles(int fila_actual, int columna_actual, int filas, int columnas, Celda **mapa, int direcciones_disponibles[4]);

// Función principal.
int main(int argc, char *argv[])
{
  // Variables locales.
  WINDOW *ventana_laberinto; // La ventana para el laberinto
  int filas,                 // El número de filas en la ventana principal
      columnas,              // El número de columnas en la ventana principal
      fila_actual,           // La fila actual para iterar sobre el mapa
      columna_actual,        // La columna actual para iterar sobre el mapa
      filas_ventana,         // Las filas para la ventana del laberinto
      columnas_ventana,      // Las columnas para la ventana del laberinto
      fila_jugador = 1,      // La fila para la posición del jugador.
      columna_jugador = 1,   // La columna para la posición del jugador.
      fila_meta,             // La fila para la posición de la meta.
      columna_meta,          // La columna para la posición de la meta.
      tecla_presionada;      // La tecla presionada.
  Celda **mapa;              // El mapa.

  // Generar la semilla aleatoria.
  srand(time(NULL));

  // Inicializar la pantalla.
  initscr();

  // Obtener dimensiones de la ventana.
  getmaxyx(stdscr, filas, columnas);

  // Calcular las dimensiones de la ventana
  filas_ventana = filas - 2;
  columnas_ventana = columnas - 2;

  // Asignamos memoria dinámicamente para el número de filas.
  mapa = malloc(filas_ventana * sizeof *mapa);

  // Iteramos sobre cada fila.
  for (fila_actual = 0; fila_actual < filas_ventana; fila_actual++)
  {
    // Asignamos memoria dinámicamente para las columnas de cada fila.
    mapa[fila_actual] = malloc(columnas_ventana * sizeof *mapa[fila_actual]);
  }

  // Limpiar pantalla inicial.
  clear();

  // No imprimir de vuelta la tecla presionada.
  noecho();

  // Sin buffer de terminal, mostrar todo lo que haya.
  cbreak();

  // Ventana para el laberinto.
  ventana_laberinto = newwin(filas_ventana, columnas_ventana, 2, 1);

  // Activamos el teclado en la ventana del laberinto.
  keypad(ventana_laberinto, TRUE);

  // Imprimimos las instrucciones para el jugador.
  mvprintw(0, 0, "Laberinto Dinámico usando ncurses.h - Sistemas Operativos ESCOM");
  mvprintw(1, 0, "Usa las flechas para moverte en la ventana, llega a la meta '%c' para ganar o presiona '%c' para salir.", CARACTER_META, OPCION_SALIR_MIN);

  // Refrescamos la ventana principal.
  refresh();

  // Generar el mapa aleatoriamente.
  busqueda_en_profundidad(1, 1, filas_ventana, columnas_ventana, mapa);

  // Colocamos el jugador en su posición inicial
  mapa[fila_jugador][columna_jugador].espacio = JUGADOR;

  // Colocamos la meta en su posición inicial.
  if (mapa[filas_ventana - 1][columnas_ventana - 1].espacio == VACIO)
  {
    fila_meta = filas_ventana - 1;
    columna_meta = columnas_ventana - 1;
  }
  else
  {
    fila_meta = filas_ventana - 2;
    columna_meta = columnas_ventana - 2;
  }
  mapa[fila_meta][columna_meta].espacio = META;

  // Mostramos el laberinto.
  imprimir_mapa(ventana_laberinto, filas_ventana, columnas_ventana, mapa);

  // Ciclo principal
  while (fila_jugador != fila_meta || columna_jugador != columna_meta)
  {
    // Leemos la tecla presionada.
    tecla_presionada = wgetch(ventana_laberinto);

    // Marcamos la posición como vacío.
    mapa[fila_jugador][columna_jugador].espacio = VACIO;

    // Actuamos en función de la tecla presionada.
    switch (tecla_presionada)
    {
    case KEY_UP:
      if (fila_jugador > 1 && mapa[fila_jugador - 1][columna_jugador].espacio != MURO)
      {
        fila_jugador -= 1;
      }
      break;

    case KEY_DOWN:
      if (fila_jugador < (filas_ventana - 1) && mapa[fila_jugador + 1][columna_jugador].espacio != MURO)
      {
        fila_jugador += 1;
      }
      break;

    case KEY_LEFT:
      if (columna_jugador > 1 && mapa[fila_jugador][columna_jugador - 1].espacio != MURO)
      {
        columna_jugador -= 1;
      }
      break;

    case KEY_RIGHT:
      if (columna_jugador < (columnas_ventana - 1) && mapa[fila_jugador][columna_jugador + 1].espacio != MURO)
      {
        columna_jugador += 1;
      }
      break;

    // Verificamos la opción de salir en minúsculas y mayúsculas por igual.
    case OPCION_SALIR_MAY:
    case OPCION_SALIR_MIN:
      return 0;
      break;

    default:
      break;
    }

    // Marcamos la posición como la actual.
    mapa[fila_jugador][columna_jugador].espacio = JUGADOR;

    // Mostramos el laberinto de nuevo.
    imprimir_mapa(ventana_laberinto, filas_ventana, columnas_ventana, mapa);
  }

  // CLR al final de línea
  clrtoeol();

  // Refrescamos la ventana.
  refresh();

  // Finalizamos la ventana principal.
  endwin();

  // Exit status = 0.
  return 0;
}

/**
 * Imprimir Mapa
 * Función que imprime, dentro de la ventana determinada, el contenido del mapa del laberinto.
 * @param ventana_laberinto Un apuntador de tipo WINDOW para la ventana que contendrá el mapa
 * @param filas El número de filas en el laberinto
 * @param columnas El número de columnas en el laberinto
 * @param mapa El mapa del laberinto
 */
void imprimir_mapa(WINDOW *ventana_laberinto, int filas, int columnas, Celda **mapa)
{
  // Variables locales.
  int fila_actual,    // La fila actual para la iteración
      columna_actual; // La columna actual para la iteración.

  // Dibujamos el contorno de la ventana del laberinto.
  box(ventana_laberinto, 0, 0);

  // Iteramos en el laberinto y mostramos los contenidos.
  for (fila_actual = 1; fila_actual < filas - 1; fila_actual++)
  {
    for (columna_actual = 1; columna_actual < columnas - 1; columna_actual++)
    {
      // Elegimos qué caracter pintar.
      switch (mapa[fila_actual][columna_actual].espacio)
      {
      case VACIO:
        mvwprintw(ventana_laberinto, fila_actual, columna_actual, "%c", CARACTER_VACIO);
        break;

      case MURO:
        mvwprintw(ventana_laberinto, fila_actual, columna_actual, "%c", CARACTER_MURO);
        break;

      case META:
        mvwprintw(ventana_laberinto, fila_actual, columna_actual, "%c", CARACTER_META);
        break;

      default:
        wattron(ventana_laberinto, A_REVERSE);
        mvwprintw(ventana_laberinto, fila_actual, columna_actual, "%c", CARACTER_JUGADOR);
        wattroff(ventana_laberinto, A_REVERSE);
        break;
      }
    }
  }

  // Refrescamos la ventana.
  wrefresh(ventana_laberinto);
}

/**
 * Búsqueda en Profundidad
 * Implementación del algoritmo de Búsqueda en Profundidad recursivo adaptado para la generación aleatoria de laberintos
 * mediante condiciones de movimiento entre nodos determinadas por el mapa.
 * @param fila_actual La fila actual en la que nos encontramos
 * @param columna_actual La columna actual en la que nos encontramos
 * @param filas El número máximo de filas en el mapaa
 * @param columnas El número máximo de columnas den el mapa
 * @param mapa El mapa en sí.
 */
void busqueda_en_profundidad(int fila_actual, int columna_actual, int filas, int columnas, Celda **mapa)
{
  // Variables locales.
  int direcciones_disponibles[4] = {0, 0, 0, 0},
      direccion;

  do
  {
    // Marcamos la ubicación actual como vacío.
    mapa[fila_actual][columna_actual].espacio = VACIO;

    // Obtenemos las direcciones disponibles ACTUALIZADAS para la celda.
    obtener_direcciones_disponibles(fila_actual, columna_actual, filas, columnas, mapa, direcciones_disponibles);

    // Verificación de caso base (sin direcciones disponibles.)
    if (!direcciones_disponibles[DIRECCION_ARRIBA] && !direcciones_disponibles[DIRECCION_ABAJO] && !direcciones_disponibles[DIRECCION_IZQUIERDA] && !direcciones_disponibles[DIRECCION_DERECHA])
    {
      return;
    }

    // Calculamos una dirección disponible aleatoria dentro de las posibilidades.
    do
    {
      direccion = rand() % 4;
    } while (direcciones_disponibles[direccion] == 0);

    // Operamos en la dirección seleccionada.
    switch (direccion)
    {
    case DIRECCION_ARRIBA:
      mapa[fila_actual - 1][columna_actual].espacio = VACIO;
      busqueda_en_profundidad(fila_actual - 2, columna_actual, filas, columnas, mapa);
      break;

    case DIRECCION_IZQUIERDA:
      mapa[fila_actual][columna_actual - 1].espacio = VACIO;
      busqueda_en_profundidad(fila_actual, columna_actual - 2, filas, columnas, mapa);
      break;

    case DIRECCION_DERECHA:
      mapa[fila_actual][columna_actual + 1].espacio = VACIO;
      busqueda_en_profundidad(fila_actual, columna_actual + 2, filas, columnas, mapa);
      break;

    case DIRECCION_ABAJO:
    default:
      mapa[fila_actual + 1][columna_actual].espacio = VACIO;
      busqueda_en_profundidad(fila_actual + 2, columna_actual, filas, columnas, mapa);
      break;
    }
  } while (direcciones_disponibles[DIRECCION_ARRIBA] || direcciones_disponibles[DIRECCION_ABAJO] || direcciones_disponibles[DIRECCION_IZQUIERDA] || direcciones_disponibles[DIRECCION_DERECHA]);
}

/**
 * Obtener Direcciones Disponibles
 * Función que rellena un arreglo con las direcciones disponibles dentro del mapa para la ubicación actual.
 * @param fila_actual La fila actual en la posición del jugador
 * @param columna_actual La columna actual en la posición del jugador
 * @param filas El número de filas totales del mapa
 * @param columnas El número de columnas totales del mapa
 * @param mapa El mapa bidimensional
 * @param direcciones_disponibles El arreglo a marcar con las direcciones disponibles
 */
void obtener_direcciones_disponibles(int fila_actual, int columna_actual, int filas, int columnas, Celda **mapa, int *direcciones_disponibles)
{
  // Arriba.
  if ((fila_actual - 2) >= 1 && mapa[fila_actual - 2][columna_actual].espacio == MURO)
  {
    direcciones_disponibles[DIRECCION_ARRIBA] = 1;
  }
  else
  {
    direcciones_disponibles[DIRECCION_ARRIBA] = 0;
  }

  // Abajo.
  if ((fila_actual + 2) <= (filas - 2) && mapa[fila_actual + 2][columna_actual].espacio == MURO)
  {
    direcciones_disponibles[DIRECCION_ABAJO] = 1;
  }
  else
  {
    direcciones_disponibles[DIRECCION_ABAJO] = 0;
  }

  // Derecha
  if ((columna_actual + 2) <= (columnas - 2) && mapa[fila_actual][columna_actual + 2].espacio == MURO)
  {
    direcciones_disponibles[DIRECCION_DERECHA] = 1;
  }
  else
  {
    direcciones_disponibles[DIRECCION_DERECHA] = 0;
  }

  // Izquierda
  if ((columna_actual - 2) >= 1 && mapa[fila_actual][columna_actual - 2].espacio == MURO)
  {
    direcciones_disponibles[DIRECCION_IZQUIERDA] = 1;
  }
  else
  {
    direcciones_disponibles[DIRECCION_IZQUIERDA] = 0;
  }
}
