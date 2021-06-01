/**
 * Práctica 8
 * 
 * Programa81.c Realizar un programa en lenguaje C en Linux que permita la creación y edición de un archivo
 * de texto. En otras palabras, crear un editor de textos básico. El programa debe permitir crear un directorio
 * nuevo si el usuario lo requiere.
 * 
 */
#include <stdio.h>    // Para operaciones estándar de entrada y salida.
#include <stdlib.h>   // Para utilizar funciones estándar de C.
#include <sys/stat.h> // Para la verificación de directorios y archivos.
#include <ncurses.h>  // Para controlar el aspecto gráfico dentro de la terminal.
#include <string.h>   // Para realizar operaciones con cadenas de caracteres.
#include <locale.h>   // Para poder mostrar acentos y caracteres especiales en la terminal.

// Constantes de operación.
#define LECTURA_ARCHIVO_OK 0
#define LECTURA_ARCHIVO_PARAMETROS_INVALIDOS -1
#define LECTURA_ARCHIVO_ERROR -2
#define LECTURA_ARCHIVO_MUY_GRANDE -3
#define LECTURA_ARCHIVO_SIN_MEMORIA -4
#define LECTURA_ARCHIVO_TAM_BLOQUE 2097152 // El tamaño de lectura de cada "bloque" de información del archivo 2MiB.
#define TAMANIO_INICIAL 2                  // El tamaño inicial del archivo si es un archivo nuevo.
#define CARACTER_VACIO ' '                 // Cuando la pantalla no debe mostrar nada
#define CARACTER_DE_CONTROL ' '            // Cuando existe un caracter de control (\0 o \n), para debuggear más fácil qué está sucediendo.

// Prototipos de funciones.
int leer_archivo_en_buffer(char *, char **, size_t *);                        // Función para leer un archivo y guardarlo en un búffer.
int existe_archivo(char *);                                                   // Función para determinar si existe un archivo.
void editor_de_texto(char *, char **, size_t *, int, int);                    // Función que encapsula la operación del editor.
void calcular_pantalla(int **, int, int, int, int, char **, size_t);          // Función que calcula los contenidos de la pantalla en cada interacción del usuario.
void mostrar_pantalla(int, int, char **, int, int, int **);                   // Función que muestra la pantalla calculada
void mostrar_estadisticas(char *, char **, size_t, int, int, int, int);       // Función que muestra estadísticas en la barra de menú.
void tecla_abajo(int, int **, int *, int *, char **, int *);                  // Función para encapsular la lógica de presionar la tecla "Flecha Abajo"
void tecla_arriba(int, int **, int *, int *, char **, int *);                 // Función para encapsular la lógica de presionar la tecla "Flecha Arriba"
void tecla_izquierda(int *, int *);                                           // Función para encapsular la lógica de presionar la tecla "Flecha Izquierda"
void tecla_derecha(int *, int *, int, size_t, char **);                       // Función para encapsular la lógica de presionar la tecla "Flecha Derecha"
void tecla_borrar(int *, int *, char **, size_t *, int *, int **);            // Función para encapsular la lógica de presionar la tecla "Borrar"
void tecla_esc(char *, char **, size_t);                                      // Función para encapsular la lógica de presionar la tecla "ESC" (salir)
void tecla_cualquiera(char **, size_t *, int, int *, int *, int, int *, int); // Función para encapsular la lógica de presionar cualquier otra tecla.

// Función principal.
int main(int argc, char *argv[])
{
  // Variables locales.
  char *buffer,                  // El búffer dónde almacenaremos el texto.
      *nombre_archivo;           // Para almacenar el nombre del archivo.
  int resultado_lectura_archivo, // Para almacenar el resultado de la lectura del archivo inicial.
      filas_maximas,             // Para almacenar el número máximo de filas en la terminal.
      columnas_maximas,          // Para almacenar el número máximo de columnas en la terminal.
      archivo_existente;         // Variable para almacenar el resultado de si el archivo existe o hay que crearlo.
  size_t tamanio_buffer;         // Para almacenar el tamaño del búffer con el contenido del archivo.

  // Verificamos si obtuvimos el nombre del archivo como parámetro del programa.
  if (argc == 2)
  {
    nombre_archivo = argv[1]; // Asumimos que el segundo parámetro es el nombre
                              // del archivo.
  }
  else
  {
    // Mostramos la información de uso del programa al usuario.
    printf("\tPráctica 8 - Editor básico de Textos\n");
    printf("NOMBRE:\n");
    printf("\t%s - Editor básico de textos\n\n", argv[0]);
    printf("USO:\n");
    printf("\t%s /ruta/al/archivo/para/editar.txt\n\n", argv[0]);
    printf("CRÉDITOS:\n");
    printf("\tEquipo:\n");
    printf("\t\t- Chávez Hernández Efraín          (2CV15)\n");
    printf("\t\t- Díaz Matus Ricardo               (2CV15)\n");
    printf("\t\t- Ortega Alcocer Humberto Alenadro (2CV15)\n");
    printf("\t\t- Sánchez Fuentes Consuelo         (2CM15)\n");
    printf("\tMateria:\n");
    printf("\t\tSistemas Operativos ESCOM - IPN\n");

    // Exit status 0.
    return 0;
  }

  // Verificamos que el archivo exista.
  archivo_existente = existe_archivo(nombre_archivo);

  // Si el archivo existe leemos su contenido.
  if (archivo_existente)
  {
    // Confirmamos con el usuario el nombre del archivo.
    printf("Leyendo '%s' ...\n", nombre_archivo);

    // Leemos el archivo en el búffer.
    resultado_lectura_archivo = leer_archivo_en_buffer(nombre_archivo, &buffer, &tamanio_buffer);

    // Verificamos la lectura del archivo.
    switch (resultado_lectura_archivo)
    {
    case LECTURA_ARCHIVO_OK:
      printf("¡Archivo leído correctamente!\n%s\n", buffer);
      break;
    case LECTURA_ARCHIVO_PARAMETROS_INVALIDOS:
      printf("El archivo no existe o está dañado, revísalo e intenta más tarde.\n");
      return -1;
    case LECTURA_ARCHIVO_ERROR:
      printf("Ocurrió un error leyendo el archivo, inténtalo más tarde.\n");
      return -1;
    case LECTURA_ARCHIVO_MUY_GRANDE:
      printf("El archivo es demasiado grande, intenta con un archivo más pequeño.\n");
      return -1;
    case LECTURA_ARCHIVO_SIN_MEMORIA:
      printf("El programa no cuenta con memoria suficiente para leer el archivo, intenta más tarde.\n");
      return -1;
    }
  }
  else
  {
    // Si el archivo no existe, inicializamos el búffer en un tamaño predefinido.
    buffer = malloc(sizeof(char) * TAMANIO_INICIAL);
    tamanio_buffer = TAMANIO_INICIAL;
    buffer[0] = EOF;
  }

  // Inicialización de nuestro ambiente de texto gráfico.
  setlocale(LC_ALL, "es_MX");                        // Colocamos la localización en español México.
  initscr();                                         // Iniciamos el modo gráfico.
  cbreak();                                          // Queremos capturar _todas_ las teclas que presione el usuario (esto incluye Control + C ¡aguas!)
  keypad(stdscr, TRUE);                              // Activamos el modo "keypad" para poder utilizar flechas del teclado y demás monerías.
  noecho();                                          // No queremos que las teclas que presione el usuario se impriman.
  getmaxyx(stdscr, filas_maximas, columnas_maximas); // Obtenemos las dimensiones de nuestra ventana.

  // Ejecutamos el editor principal.
  editor_de_texto(nombre_archivo, &buffer, &tamanio_buffer, filas_maximas, columnas_maximas);

  // Finalización del programa.
  clear();  // Limpiar la ventana.
  endwin(); // Finalizamos la ventana.

  // Liberamos la memoria del búffer.
  free(buffer);

  // Exit status = 0.
  return 0;
}

/**
 * Leer archivo en búffer
 * Esta función toma un nombre de archivo, lee sus contenidos de forma eficiente utilizando bloques
 * de memoria dinámica para evitar leer "caracter a caracter" y, finalmente, coloca los resultados
 * en dos apuntadores.
 * @param nombre_archivo El nombre del archivo a abrir.
 * @param buffer_final El buffer final dónde colocaremos los contenidos del archivo.
 * @param tamanio Un apuntador para almacenar el tamaño final del búffer con los contenidos del archivo.
 * @return Un entero con una bandera indicando el estado de operación de la función.
 */
int leer_archivo_en_buffer(char *nombre_archivo, char **buffer_final, size_t *tamanio)
{
  // Variables locales
  char *buffer = NULL,
       *temporal;
  size_t tam = 0,
         usado = 0,
         n;
  FILE *archivo;

  // Abrimos el archivo en modo solo lectura.
  archivo = fopen(nombre_archivo, "rb");

  // Validación de parámetros
  if (archivo == NULL || buffer_final == NULL || tamanio == NULL)
  {
    // Alguno de los parámetros proporcionados es inválido.
    return LECTURA_ARCHIVO_PARAMETROS_INVALIDOS;
  }

  // Verificamos que no haya errores de lectura previos.
  if (ferror(archivo))
  {
    return LECTURA_ARCHIVO_ERROR;
  }

  // Ciclo principal de lectura.
  while (1)
  {
    // Verificamos si llegamos al límite de lectura por "bloque".
    if ((usado + LECTURA_ARCHIVO_TAM_BLOQUE + 1) > tam)
    {
      // Ajustamos el tamaño apropiadamente (siempre considerando EOF)
      tam = usado + LECTURA_ARCHIVO_TAM_BLOQUE + 1;

      // Checamos que no se desborden las variables, existen compiladores que optimizan esto automágicamente.
      if (tam <= usado)
      {
        // Liberamos el buffer.
        free(buffer);
        // Regresamos el error de que el archivo es más grande de lo que disponemos de memoria.
        return LECTURA_ARCHIVO_MUY_GRANDE;
      }

      // Movemos la memoria desde nuestro buffer a la variable temporal.
      temporal = realloc(buffer, tam);

      // Verificamos que aún tengamos memoria de "heap" disponible.
      if (temporal == NULL)
      {
        // Liberamos el búffer.
        free(buffer);

        // Regresamos el error de que nos quedamos sin memoria de "heap" suficiente.
        return LECTURA_ARCHIVO_SIN_MEMORIA;
      }

      // Asiganmos de vuelta el búffer.
      buffer = temporal;
    }

    // Usamos la variable temporal para medir la cantidad de datos que fueron leídos por la función.
    n = fread(buffer + usado, 1, LECTURA_ARCHIVO_TAM_BLOQUE, archivo);

    // Verificamos si terminamos de leer el archivo.
    if (n == 0)
    {
      break;
    }

    // Aumentamos el contador de memoria utilizada.
    usado += n;
  }

  // Verificamos que no haya existido un error de lectura.
  if (ferror(archivo))
  {
    // Liberamos el buffer.
    free(buffer);

    // Regresamos el error.
    return LECTURA_ARCHIVO_ERROR;
  }

  // Asignamos los datos leídos desde el buffer temporal.
  buffer = temporal;

  // Movemos la memoria desde nuestro buffer a la variable temporal.
  temporal = realloc(buffer, tam);

  // Verificamos que aún tengamos memoria de "heap" disponible.
  if (temporal == NULL)
  {
    // Liberamos el búffer.
    free(buffer);

    // Regresamos el error de que nos quedamos sin memoria de "heap" suficiente.
    return LECTURA_ARCHIVO_SIN_MEMORIA;
  }

  // Asiganmos de vuelta el búffer.
  buffer = temporal;

  // Asignamos el EOF.
  buffer[tam] = '\0';

  // Cerramos el archivo.
  fclose(archivo);

  // Asignamos los datos leídos a los apuntadores de resultados.
  *buffer_final = buffer;
  *tamanio = usado;

  // Regresamos la bandera de éxito.
  return LECTURA_ARCHIVO_OK;
}

/**
 * Existe Archivo
 * Esta función toma un nombre de archivo y determina si existe o no, regresando 1 si existe o 0 en
 * caso contrario.
 * @param nombre_archivo El nombre del archivo a probar si existe.
 * @return Un entero 1 si el archivo existe o 0 en otro caso.
 */
int existe_archivo(char *nombre_archivo)
{
  // Variables locales.
  struct stat buffer; // Búffer para almacenar el resultado de stat().

  // Regresamos el valor de stat().
  return (stat(nombre_archivo, &buffer) == 0);
}

/**
 * Editor de texto
 * Función que contiene el ciclo principal de ejecución para navegación y edición de un búffer de texto
 * mientras el usuario no presione la tecla ESC.
 * @param buffer Un apuntador al búffer de memoria dónde se encuentra el contenido del archivo a editar
 * @param tamanio_buffer Un apuntador al tamaño del búffer de memoria
 * @param filas_maximas El número máximo de filas de nuestra terminal
 * @param columnas_maximas El número máximo de columnas de nuestra terminal.
 * @return void
 */
void editor_de_texto(char *nombre_archivo, char **buffer, size_t *tamanio_buffer, int filas_maximas, int columnas_maximas)
{
  // Variables locales.
  int tecla_presionada, // Variable para almacenar la tecla presionada por el usuario.
      pos_x,            // Variable para almacenar la posición en x (columna) de nuestra pantalla.
      pos_y,            // Variable para almacenar la posición en y (fila) de nuestra pantalla.
      pos_buffer,       // Variable para almacenar nuestra posición actual dentro del búffer de memoria.
      fila_actual,      // Variable para iterar sobre las filas.
      **pantalla;       // Variable para almacenar nuestra pantalla.

  // Creamos "filas_maximas - 1" filas (la primer fila es para estadísticas) en nuestra pantalla.
  pantalla = (int **)malloc((filas_maximas - 1) * sizeof(int *));

  // Iteramos sobre cada fila de la pantalla.
  for (fila_actual = 0; fila_actual < (filas_maximas - 1); fila_actual++)
  {
    // Generamos el arreglo de "columnas_maximas" columnas para cada fila.
    pantalla[fila_actual] = (int *)malloc(columnas_maximas * sizeof(int));
  }

  // Colocamos la posición inicial del cursor y de la posición en el búffer.
  pos_x = 0;
  pos_y = 0;
  pos_buffer = 0;

  // Ciclo principal de ejecución.
  do
  {
    // Calculamos la pantalla actual a partir de la posición del búffer y coordenadas de cursor actuales.
    calcular_pantalla(pantalla, filas_maximas, columnas_maximas, pos_y, pos_buffer, buffer, *tamanio_buffer);

    // Mostrar el contenido del archivo corresopndiente a la ventana.
    mostrar_pantalla(pos_x, pos_y, buffer, filas_maximas, columnas_maximas, pantalla);

    // Mostramos las coordenadas y posición en el búffer
    mostrar_estadisticas(nombre_archivo, buffer, *tamanio_buffer, pos_x, pos_y, pos_buffer, columnas_maximas);

    // Leemos la tecla que presiona el usuario.
    tecla_presionada = getch();

    // Si la tecla no es ESC, editamos el búffer apropiadamente.
    switch (tecla_presionada)
    {
    case 27:
      tecla_esc(nombre_archivo, buffer, *tamanio_buffer);
      break;

    case KEY_UP:
      tecla_arriba(columnas_maximas, pantalla, &pos_y, &pos_x, buffer, &pos_buffer);
      break;

    case KEY_DOWN:
      tecla_abajo(filas_maximas, pantalla, &pos_y, &pos_x, buffer, &pos_buffer);
      break;

    case KEY_LEFT:
      tecla_izquierda(&pos_x, &pos_buffer);
      break;

    case KEY_RIGHT:
      tecla_derecha(&pos_x, &pos_buffer, columnas_maximas, (*tamanio_buffer), buffer);
      break;

    case 127:
      tecla_borrar(&pos_x, &pos_y, buffer, tamanio_buffer, &pos_buffer, pantalla);
      break;

    default:
      tecla_cualquiera(buffer, tamanio_buffer, tecla_presionada, &pos_buffer, &pos_x, columnas_maximas, &pos_y, filas_maximas);
      break;
    }
  } while (tecla_presionada != 27); // Mientras el usuario no presiones ESC.

  // Limpiar memoria.
  free(pantalla);
}

/**
 * Calcular Pantalla
 * Función que calcula los contenidos de la pantalla a partir de una serie de datos que indican la posición actual tanto en la pantalla misma como en
 * el búffer de contenido.
 * @param pantalla La matriz con la pantalla a modificar
 * @param filas_maximas El número máximo de filas existentes en la pantalla
 * @param columnas_maximas El número máximo de columnas existentes en la pantalla
 * @param pos_y La posición actual en y (filas) del cursor
 * @param pos_buffer La posición actual en el búffer de contenido
 * @param buffer El búffer per sé para realizar cálculos
 * @param tamanio_buffer El tamaño del búffer
 * @return void
 */
void calcular_pantalla(int **pantalla, int filas_maximas, int columnas_maximas, int pos_y, int pos_buffer, char **buffer, size_t tamanio_buffer)
{
  // Variables locales.
  int pos_buffer_temporal,
      pos_x_temporal,
      pos_y_temporal,
      lineas_antes;

  // Llenamos la pantalla de -1's.
  for (pos_y_temporal = 0; pos_y_temporal < (filas_maximas - 1); pos_y_temporal++)
  {
    for (pos_x_temporal = 0; pos_x_temporal < columnas_maximas; pos_x_temporal++)
    {
      pantalla[pos_y_temporal][pos_x_temporal] = -1;
    }
  }

  // Calculamos el número de líneas previas a la posición actual en el búffer mientras reducimos dicha posición.
  for (pos_buffer_temporal = pos_buffer - 1, lineas_antes = 0; pos_buffer_temporal > 0 && lineas_antes < pos_y; pos_buffer_temporal--)
  {
    if ((*buffer)[pos_buffer_temporal] == '\n')
    {
      lineas_antes += 1;
    }
  }

  if (pos_buffer_temporal == -1)
  {
    pos_buffer_temporal = 0;
  }

  // Reducimos la posición del búffer para encontrar el principio de la línea inicial.
  while (pos_buffer_temporal > 0 && (*buffer)[pos_buffer_temporal - 1] != '\n')
  {
    pos_buffer_temporal--;
  }

  // Iteramos sobre cada fila de la pantalla hasta encontrar el fin del búffer.
  for (pos_y_temporal = 0; pos_y_temporal < (filas_maximas - 1) && pos_buffer_temporal < ((int)(tamanio_buffer)) && (*buffer)[pos_buffer_temporal] != '\0'; pos_y_temporal++, pos_buffer_temporal++)
  {
    // Iteramos sobre cada columna y caracter del búffer.
    for (pos_x_temporal = 0; pos_x_temporal < columnas_maximas && pos_buffer_temporal < ((int)(tamanio_buffer)) && (*buffer)[pos_buffer_temporal] != '\n' && (*buffer)[pos_buffer_temporal] != '\0'; pos_x_temporal++, pos_buffer_temporal++)
    {
      // Asignamos el valor presente en el búffer.
      pantalla[pos_y_temporal][pos_x_temporal] = pos_buffer_temporal;
    }

    // Verificamos si nuestro último caracter fue un salto de línea o EOL y en caso contrario sólamente recorremos hasta encontrarlo.
    if ((*buffer)[pos_buffer_temporal] != '\n' && (*buffer)[pos_buffer_temporal] != '\0')
    {
      while (pos_buffer_temporal < ((int)(tamanio_buffer)) && (*buffer)[pos_buffer_temporal] != '\n' && (*buffer)[pos_buffer_temporal] != '\0')
      {
        pos_buffer_temporal++;
      }
    }

    // Asignamos el último caracter encontrado a nuestra posición.
    pantalla[pos_y_temporal][pos_x_temporal] = pos_buffer_temporal;
  }
}

/**
 * Tecla Abajo
 * Esta función contiene la lógica y el manejo de distintos escenarios al presionar la tecla "Flecha Abajo" con la cual el usuario puede desplazarse
 * una fila debajo por su selección actual si cumple ciertos criterios.
 * @param filas_maximas El número máximo de filas presentes en la pantalla actual.
 * @param pantalla Una matriz de enteros con (filas_maximas) filas y (columnas_maximas) columnas con los índices del búffer mostrados en pantalla.
 * @param pos_y Un apuntador a la variable que contiene la posición actual en y (filas) de la pantalla.
 * @param pos_x Un apuntador a la variable que contiene la posición actual en x (columnas) de la pantalla.
 * @param pos_buffer Un apuntador a la variable que contiene la posición actual en el búffer con el contenido del archivo.
 * @return void
 */
void tecla_abajo(int filas_maximas, int **pantalla, int *pos_y, int *pos_x, char **buffer, int *pos_buffer)
{
  // Variables locales.
  int pos_x_temporal,
      pos_y_temporal,
      pos_buffer_temporal;

  // Primero verificamos si aún hay filas presentes en la pantalla por debajo de la posición actual.
  if ((*pos_y) < (filas_maximas - 2))
  {
    // Aumentamos nuestra posición en y.
    pos_y_temporal = (*pos_y) + 1;
    pos_x_temporal = (*pos_x);

    // Verificamos que no sea un espacio vacío.
    if (pantalla[pos_y_temporal][pos_x_temporal] == -1)
    {
      // Si es un espacio vacío (en x) reducimos la coordenada hasta encontrar un texto.
      while (pantalla[pos_y_temporal][pos_x_temporal] == -1 && pos_x_temporal)
      {
        pos_x_temporal--;
      }

      // Si la coordenada en la posición encontrada contiene texto, asignamos la posición en el búffer
      // en otro caso descartamos la operación.
      if (pantalla[pos_y_temporal][pos_x_temporal] != -1)
      {
        (*pos_buffer) = pantalla[pos_y_temporal][pos_x_temporal];
        (*pos_y) = pos_y_temporal;
        (*pos_x) = pos_x_temporal;
      }
    }
    else
    {
      // Si no es un espacio vacío, asignamos directamente.
      (*pos_buffer) = pantalla[pos_y_temporal][pos_x_temporal];
      (*pos_y) = pos_y_temporal;
      (*pos_x) = pos_x_temporal;
    }
  }
  else
  {
    // En caso de que no haya filas presentes en la pantalla por debajo de la posición actual, debemos verificar que contemos, entonces,
    // con una siguiente línea en el búffer.
    for (pos_buffer_temporal = (*pos_buffer); (*buffer)[pos_buffer_temporal] != '\n' && (*buffer)[pos_buffer_temporal] != '\0'; pos_buffer_temporal++)
      ;

    // Si el caracter encontrado NO es un EOL (es un \n), entonces procedemos con otras verificaciones.
    if ((*buffer)[pos_buffer_temporal] == '\n')
    {
      // Aumentamos la posición del búffer temporal a la siguiente línea.
      pos_buffer_temporal++;

      // Lo primero será calcular la posición de x en la línea más cercana a la posición actual.
      for (pos_x_temporal = 0; pos_x_temporal < (*pos_x) && (*buffer)[pos_buffer_temporal + pos_x_temporal] != '\n' && (*buffer)[pos_buffer_temporal + pos_x_temporal] != '\0'; pos_x_temporal++)
        ;

      // Asignamos la posición en x encontrada a nuestra variable.
      (*pos_x) = pos_x_temporal;
      (*pos_buffer) = pos_buffer_temporal;
    }
  }
}

/**
 * Tecla Arriba
 * Función que contiene la lógica necesaria a desarrollar cuando un usuario presiona la tecla "Flecha Arriba" con la cual el usuario puede desplazarse una línea
 * arriba considerando el caso dónde existen más líneas por debajo de la posición disponible en la pantalla.
 * @param columnas_maximas El número máximo de columnas en nuestra pantalla
 * @param pantalla La matriz con el contenido de la pantalla
 * @param pos_y Un apuntador a nuestra variable con la posición en y (filas) actual
 * @param buffer El búffer en memoria actual
 * @param pos_buffer Un apuntador a nuestra variable con la posición actual dentro del búffer de memoria
 * @return void
 */
void tecla_arriba(int columnas_maximas, int **pantalla, int *pos_y, int *pos_x, char **buffer, int *pos_buffer)
{
  // Variables locales.
  int pos_y_temporal = (*pos_y),
      pos_x_temporal = (*pos_x),
      pos_buffer_temporal = (*pos_buffer);

  // Verificamos si aún disponemos de líneas disponibles en pantalla.
  if (pos_y_temporal)
  {
    // Reducimos nuestra posición en y.
    pos_y_temporal--;

    // Verificamos que no sea un espacio vacío.
    if (pantalla[pos_y_temporal][pos_x_temporal] == -1)
    {
      // Si es un espacio vacío (en x) reducimos la coordenada hasta encontrar un texto.
      while (pantalla[pos_y_temporal][pos_x_temporal] == -1 && pos_x_temporal)
      {
        pos_x_temporal--;
      }
    }

    // Asignamos la posición del búffer a la indicada por la pantalla.
    (*pos_buffer) = pantalla[pos_y_temporal][pos_x_temporal];

    // Asignamos las variables calculadas.
    (*pos_y) = pos_y_temporal;
    (*pos_x) = pos_x_temporal;
  }
  else
  {
    if (pos_buffer_temporal > 0 && (*buffer)[pos_buffer_temporal] == '\n')
    {
      --pos_buffer_temporal;
    }

    // En caso de que no dispongamos de líneas disponibles arriba en la pantalla, verificamos si contamos con líneas previas en el búffer.
    while (pos_buffer_temporal > 0 && (*buffer)[pos_buffer_temporal] != '\n')
    {
      pos_buffer_temporal--;
    }

    // En caso de que si contemos con líneas previas, cargamos la línea inmediata anterior.
    if (pos_buffer_temporal > 0 && (*buffer)[pos_buffer_temporal] == '\n')
    {
      for (pos_x_temporal = 0; pos_x_temporal < columnas_maximas && (pos_buffer_temporal - pos_x_temporal) > 0 && (*buffer)[pos_buffer_temporal - pos_x_temporal] != '\n'; pos_x_temporal++)
        ;

      (*pos_buffer) = pos_buffer_temporal;
      (*pos_x) = pos_x_temporal;
    }
  }
}

/**
 * Tecla Izquierda
 * Función que encapsula la lógica necesaria para manejar el caso dónde el usuario presiona la tecla "Flecha Izquierda" con la cual el usuario puede desplazarse
 * una unidad a la izquierda en el eje x (columnas).
 * @param pos_x Un apuntador a nuestra variable con la posición en x (columnas) dentro de nuestra pantalla.
 * @param pos_buffer Un apuntador a nuestra variable con la posición actual dentro del búffer de memoria.
 * @return void
 */
void tecla_izquierda(int *pos_x, int *pos_buffer)
{
  // En caso de que sea posible, reducimos la posición en x del cursor.
  if ((*pos_x) && (*pos_buffer))
  {
    (*pos_x)--;
    (*pos_buffer)--;
  }
}

/**
 * Tecla Derecha
 * Función que encapsula la lógica necesaria para manejar el caso dónde el usuario presiona la tecla "Flecha Derecha" con la cual el usuario puede desplazarse,
 * si existen caracteres válidos en la pantalla, una unidad hacia la derecha.
 * @param pos_x Un apuntador a nuestra posición actual en x (columna) en la pantalla
 * @param pos_buffer Un apuntador a nuestra posición actual dentro del búffer
 * @param columnas_maximas El número máximo de columnas presentes en nuestra pantalla.
 * @param tamanio_buffer El tamaño máximo de nuestro búffer de memoria
 * @param buffer Nuestro búffer en memoria
 * @return void
 */
void tecla_derecha(int *pos_x, int *pos_buffer, int columnas_maximas, size_t tamanio_buffer, char **buffer)
{
  // En caso de que sea posible, aumentamos la posición en x del cursor.
  if ((*pos_x) < columnas_maximas && (*pos_buffer) < ((int)tamanio_buffer) && (*buffer)[(*pos_buffer)] != '\n' && (*buffer)[(*pos_buffer)] != '\0')
  {
    (*pos_x)++;
    (*pos_buffer)++;
  }
}

/**
 * Tecla Borrar
 * Función que encapsula la lógica necesaria para manejar el caso dónde el usuario presiona la tecla "Borrar" con la cual el usuario puede eliminar el caracter
 * presente en la ubicación actual en pantalla.
 * @param pos_x
 * @param pos_y
 * @param buffer
 * @param tamanio_buffer
 * @param pos_buffer
 * @param pantalla
 * @return void
 */
void tecla_borrar(int *pos_x, int *pos_y, char **buffer, size_t *tamanio_buffer, int *pos_buffer, int **pantalla)
{
  // Verificamos que estemos en una posición válida para eliminar el caracter.
  if ((*pos_buffer) - 1 >= 0)
  {
    // Reducimos el tamaño de la memoria y recorremos la memoria restante en nuestro búffer un caracter.
    memmove(&(*buffer)[(*pos_buffer) - 1], &(*buffer)[(*pos_buffer)], ((int)(--(*tamanio_buffer))) * sizeof(*(*buffer)));

    // Reducimos nuestra posición en el búffer.
    (*pos_buffer)--;

    // Verificamos si podemos reducir nuestra posición en x actual en la pantalla (columnas)
    if ((*pos_x))
    {
      (*pos_x)--;
    }
    else if ((*pos_y))
    {
      // En caso de que no podamos reducir nuestra posición en x (columnas) pero si en y (filas), buscamos el último caracter
      // de la siguiente línea en el búffer.
      while (pantalla[(*pos_y) - 1][(*pos_x) + 1] != -1)
      {
        (*pos_x)++;
      }
      (*pos_y)--;
    }
  }
}

/**
 * Tecla Cualquiera
 * Función que encapsula el comportamiento del programa en caso de que el usuario presione una tecla que no es de control, es decir, cuando desea
 * escribir dentro del documento abierto en cuestión. Para ésto, aumentaremos el tamaño de nuestro búffer y recorreremos sus contenidos en una
 * posición, colocando en la posición actual el caracter presionado por el usuario.
 * @param buffer El búffer dónde se almacena la información del archivo
 * @param tamanio_buffer Un apuntador a la variable con el tamaño actual del búffer
 * @param tecla_presionada Un entero con el código de la tecla que presionó el usuario
 * @param pos_buffer La posición actual en el búffer
 * @param pos_x La posición actual en x (columna) de nuestra pantalla
 * @param columnas_maximas El número máximo de columnas en nuestra pantalla
 * @param pos_y La posición actual en y (fila) de nuestra pantalla
 * @param filas_maximas El número máximo de filas en nuestra pantalla
 * @return void
 */
void tecla_cualquiera(char **buffer, size_t *tamanio_buffer, int tecla_presionada, int *pos_buffer, int *pos_x, int columnas_maximas, int *pos_y, int filas_maximas)
{
  // Variables locales.
  int pos_buffer_temporal; // Para iterar dentro de nuestro búffer de memoria.
  char *buffer_temporal;   // Para realizar la copia del búffer.

  // Creamos un nuevo búffer con el tamaño aumentado.
  buffer_temporal = malloc(((*tamanio_buffer) + 1) * sizeof(char));

  for (pos_buffer_temporal = 0; pos_buffer_temporal < (*pos_buffer); pos_buffer_temporal++)
  {
    buffer_temporal[pos_buffer_temporal] = (*buffer)[pos_buffer_temporal];
  }

  // Recorremos los elementos dentro de nuestro búffer de memoria en una unidad.
  for (pos_buffer_temporal = ((int)(*tamanio_buffer)); pos_buffer_temporal > (*pos_buffer); pos_buffer_temporal--)
  {
    buffer_temporal[pos_buffer_temporal] = (*buffer)[pos_buffer_temporal - 1];
  }

  // Si la tecla es "Enter", manualmente colocamos el caracter y aumentamos nuestra posición en y.
  if (tecla_presionada == '\n')
  {
    // Asignamos el salto de línea al búffer.
    buffer_temporal[pos_buffer_temporal] = '\n';

    // Verificamos si podemos aumentar la coordenada en y.
    if ((*pos_y) < (filas_maximas - 1))
    {
      (*pos_y)++;
      (*pos_x) = 0;
    }
  }
  else
  {
    // Si es cualquier otra tecla, hacemos un casting a caracter con su código ASCII.
    buffer_temporal[pos_buffer_temporal] = (char)tecla_presionada;
  }

  // Aumentamos el tamaño del búffer.
  (*tamanio_buffer) += 1;

  // Borramos el búffer anterior.
  free((*buffer));

  // Asignamos el nuevo búffer.
  (*buffer) = buffer_temporal;

  // Aumentamos la posición dentro del búffer.
  (*pos_buffer) += 1;

  // Si es posible, aumentamos la posición en x (columna) en nuestra pantalla actualmente.
  if ((*pos_x + 1) < columnas_maximas)
  {
    (*pos_x)++;
  }
}

/**
 * Tecla ESC
 * Función que encapsula la lógica detrás de un usuario presionando la tecla "ESC" con la cual se abandona el programa. En esta función,
 * abrimos el archivo que nos especificó el usuario al invocar el programa y almacenamos los contenidos del búffer dentro del mismo.
 * @param nombre_archivo El nombre del archivo para almacenar los datos.
 * @param buffer El búffer con los datos que deseamos guardar en el archivo
 * @param tamanio_buffer El tamaño del búffer para almacenar
 * @return void
 */
void tecla_esc(char *nombre_archivo, char **buffer, size_t tamanio_buffer)
{
  // Variables locales
  FILE *archivo; // El archivo a abrir para guardar los datos.

  // Abrimos el archivo en modo escritura.
  archivo = fopen(nombre_archivo, "w");

  // Verificamos que se haya podido abrir el archivo.
  if (archivo == NULL)
  {
    // En caso de que no se haya podido abrir, abandonamos con exit status = -1.
    exit(-1);
    return;
  }

  // Verificamos que el búffer esté terminado con un EOF, sino, lo añadimos.
  if ((*buffer)[tamanio_buffer] != EOF)
  {
    (*buffer)[tamanio_buffer] = EOF;
  }

  // Guardamos nuestro búffer en el archivo.
  fwrite(*buffer, sizeof(char), tamanio_buffer, archivo);

  // Cerramos el archivo.
  fclose(archivo);
}

/**
 * Mostrar Pantalla
 * Función que imprime la matriz correspondiente a la pantalla en la, vaya, pantalla de terminal sustituyendo los valores presentes
 * en dicha matriz por el elemento i-ésimo presente en el búffer con los datos.
 * @param pos_x La posición en el eje x actual en la pantalla.
 * @param pos_y La posición en el eje y actual en la pantalla.
 * @param buffer El búffer de memoria con los contenidos del archivo.
 * @param filas_maximas Las filas máximas presentes en la pantalla.
 * @param columnas_maximas Las columnas máximas presentes en la pantalla.
 * @param pantalla Una matriz con los contenidos de la pantalla.
 * @return void
 */
void mostrar_pantalla(int pos_x, int pos_y, char **buffer, int filas_maximas, int columnas_maximas, int **pantalla)
{
  // Variables locales.
  char caracter_temporal; // Caracter temporal para operaciones de impresión.
  int fila_actual,        // Iterador para las filas de la matriz.
      columna_actual;     // Iterador para las columnas de la matriz.

  // Iteramos en las filas de la matriz.
  for (fila_actual = 0; fila_actual < (filas_maximas - 1); fila_actual++)
  {
    // Iteramos sobre las columnas de la matriz.
    for (columna_actual = 0; columna_actual < columnas_maximas; columna_actual++)
    {
      // Si es la posición de nuestro cursor, activamos el modo invertido para imprimir el texto.
      if (fila_actual == pos_y && columna_actual == pos_x)
      {
        attron(A_REVERSE);
      }

      // Seleccionamos el tipo de caracter a imprimir.
      if (pantalla[fila_actual][columna_actual] == -1)
      {
        // En caso de estar vacío, imprimimos un caracter vacío.
        caracter_temporal = CARACTER_VACIO;
      }
      else if ((*buffer)[pantalla[fila_actual][columna_actual]] == '\n' || (*buffer)[pantalla[fila_actual][columna_actual]] == '\0')
      {
        // En caso de ser EOL o un salto de línea, usamos un caracter de control.
        caracter_temporal = CARACTER_DE_CONTROL;
      }
      else
      {
        // En cualquier otro caso, mostramos el caracter presente en el índice almacenado en pantalla.
        caracter_temporal = (*buffer)[pantalla[fila_actual][columna_actual]];
      }

      // Imprimimos el caracter correspondiente en la coordenada actual.
      mvprintw(fila_actual + 1, columna_actual, "%c", caracter_temporal);

      // Si es la posición de nuestro cursor, desactivamos el modo invertido para imprimir el texto.
      if (fila_actual == pos_y && columna_actual == pos_x)
      {
        attroff(A_REVERSE);
      }
    }
  }
}

/**
 * Mostrar Estadísticas
 * Función que muestra las estadísticas de operación del editor en la esquina superior derecha.
 * @param pos_x La posición actual del cursor en el eje x (columnas).
 * @param pos_y La posición actual del cursor en el eje y (filas).
 * @param pos_buffer La posición actual dentro del búffer de contenido.
 * @param columnas_maximas El número máximo de columnas en la pantalla.
 * @return void
 */
void mostrar_estadisticas(char *nombre_archivo, char **buffer, size_t tamanio_buffer, int pos_x, int pos_y, int pos_buffer, int columnas_maximas)
{
  // Variables locales.
  int lineas,
      linea_actual,
      pos_buffer_temporal;

  // Ciclo para contar el número de líneas presentes en nuestro editor actual.
  for (pos_buffer_temporal = 0, lineas = 0, linea_actual = 0; pos_buffer_temporal < ((int)tamanio_buffer); pos_buffer_temporal++)
  {
    // Para saber la línea actual, contabilizamos únicamente aquellas antes de nuestra posición actual en el búffer.
    if (pos_buffer_temporal < pos_buffer)
    {
      linea_actual += (*buffer)[pos_buffer_temporal] == '\n';
    }

    // Contabilización de líneas generales.
    lineas += (*buffer)[pos_buffer_temporal] == '\n';
  }

  // Mostramos el "menú" de nuestro editor.
  attron(A_REVERSE);
  mvhline(0, 0, '#', columnas_maximas);
  mvprintw(0, 0, "Editando \"%s\" %s | ESC para Guardar y Salir | Líneas: %i | Línea Actual: %i | Col: %i | Fila: %i | Pos. Búffer: %i", nombre_archivo, existe_archivo(nombre_archivo) ? "" : "(Nuevo)", lineas, linea_actual, pos_x, pos_y, pos_buffer);
  attroff(A_REVERSE);
}
