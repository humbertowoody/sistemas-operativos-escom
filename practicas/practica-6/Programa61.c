/**
 * Programa61.c
 * 
 * Realizar un programa que simule la memoria virtual que cumpla con las siguientes  indicaciones: 
 *  • La memoria virtual es de 64 KB 
 *  • La memoria física es de 32 KB 
 *  • El tamaño de página es de 4 KB 
 *  • El programa debe indicar que páginas se encuentran en la memoria física 
 *  • Se le indicará al programa manualmente que página se desea insertar a la memoria física 
 *  • Cuando se le indique deberá hacer la transformación de todas las direcciones de la página mostrando ambas direcciones en cada transformación 
 *  • En el momento que se indica la página que se va a mover a la memoria física se debe aplicar un algoritmo de fallo de página 
 *  • Las páginas se administrarán mediante una tabla de páginas que debe estar programada mediante listas
 */
#include <stdio.h>  // Operaciones estándar de E/S.
#include <stdlib.h> // Funciones de la librería estándar de C.

// Constantes de operación.
#define NUM_PAGINAS 16
#define NUM_PAGINAS_MARCO 8
#define MENU_MOSTRAR_TABLA_DE_PAGINAS 1
#define MENU_MOSTRAR_TABLA_DE_MARCOS_DE_PAGINA 2
#define MENU_INSERTAR_PAGINA_EN_RAM 3
#define MENU_SALIR 4

// Estructura para lista ligada.
typedef struct marco_pagina
{
  int id_marco;                   // El identificador del marco de página.
  int id_pagina;                  // El identificador del marco de página cargado actualmente en memoria.
  struct marco_pagina *siguiente; // Un apuntador al siguiente elemento de la lista ligada.
} MarcoPagina;

// Prototipos de funciones.
void mostrar_tabla_de_paginas(MarcoPagina *marco_de_pagina_inicial);
void mostrar_tabla_de_marcos_de_pagina(MarcoPagina *marco_de_pagina_inicial);
void insertar_en_ram(int id_pagina_a_insertar, MarcoPagina **marco_de_pagina_inicial);
MarcoPagina *buscar_pagina_en_ram(int, MarcoPagina *);

// Función principal.
int main(int argc, char *argv[])
{
  // Variables locales.
  MarcoPagina *marco_de_pagina_inicial = NULL; // El marco de página (RAM) inicia vacío.
  int opcion_menu,
      id_pagina_a_insertar;

  // Ciclo principal de ejecución del programa.
  do
  {
    // Imprimir el menú.
    printf("\tMenú Principal\n\n");
    printf("Opciones disponibles:\n");
    printf(" %i) Mostrar tabla de páginas.\n", MENU_MOSTRAR_TABLA_DE_PAGINAS);
    printf(" %i) Mostrar tabla de marcos de página.\n", MENU_MOSTRAR_TABLA_DE_MARCOS_DE_PAGINA);
    printf(" %i) Insertar página en RAM (marco de página).\n", MENU_INSERTAR_PAGINA_EN_RAM);
    printf("\n");
    printf(" %i) Salir del programa.\n", MENU_SALIR);
    printf("\n");

    // Leer entrada (con validación).
    do
    {
      printf("[%i - %i]> ", MENU_MOSTRAR_TABLA_DE_PAGINAS, MENU_SALIR);
      scanf("%i", &opcion_menu);
    } while (opcion_menu < MENU_MOSTRAR_TABLA_DE_PAGINAS || opcion_menu > MENU_SALIR);

    // Realizamos la operación seleccionada por el usuario.
    switch (opcion_menu)
    {
    // Opción para mostrar la tabla de páginas.
    case MENU_MOSTRAR_TABLA_DE_PAGINAS:
      mostrar_tabla_de_paginas(marco_de_pagina_inicial);
      break;

    // Opción para mostrar la tabla de marcos de página.
    case MENU_MOSTRAR_TABLA_DE_MARCOS_DE_PAGINA:
      mostrar_tabla_de_marcos_de_pagina(marco_de_pagina_inicial);
      break;

    // Opción para mover una página a la RAM.
    case MENU_INSERTAR_PAGINA_EN_RAM:
      // Leemos el ID de la página a insertar en la RAM.
      printf("Ingrese el ID de la página a insertar en la RAM:\n");
      do
      {
        printf("[0 - %i]> ", NUM_PAGINAS - 1);
        scanf("%i", &id_pagina_a_insertar);
      } while (id_pagina_a_insertar < 0 || id_pagina_a_insertar >= NUM_PAGINAS); // Validación de entrada.

      // Realizamos la inserción.
      insertar_en_ram(id_pagina_a_insertar, &marco_de_pagina_inicial);
      break;

    // Opción para cuando el usuario desea salir o es una opción no contemplada.
    case MENU_SALIR:
    default:
      printf("¡Gracias por utilizar este programa!\n\n");
      break;
    }

  } while (opcion_menu != MENU_SALIR); // Validación.

  // Fin de ejecución.
  return 0;
}

/**
 * Mostrar Tabla de Páginas
 * Función que imprime a la salida estándar el contenido de la tabla de páginas incluyendo, si la hay,
 * el índice del marco de página dónde se encuentra la página cargada en ese momento.
 * @param marco_de_pagina_inicial El marco de página inicial para poder verificar las páginas que se encuentran en RAM.
 * @return void
 */
void mostrar_tabla_de_paginas(MarcoPagina *marco_de_pagina_inicial)
{
  // Variables locales.
  MarcoPagina *marco_de_pagina_encontrado = NULL;

  // Imprimimos el encabezado.
  printf("Tabla de páginas:\n\n");
  printf("----------------------------------\n");
  printf("| ID Página | ID Marco de Página |\n");
  printf("----------------------------------\n");

  // Iteramos sobre el número de páginas especificadas para el programa.
  for (int i = 0; i < NUM_PAGINAS; i++)
  {
    // Buscamos algún marco de página dónde esté cargada la página actual.
    marco_de_pagina_encontrado = buscar_pagina_en_ram(i, marco_de_pagina_inicial);

    // Verificamos si lo encontramos.
    if (marco_de_pagina_encontrado != NULL)
    {
      printf("| %9i | %18i |\n", i, marco_de_pagina_encontrado->id_marco);
    }
    else
    {
      printf("| %9i | %18s |\n", i, "Sin cargar en RAM.");
    }
  }

  // Imprimimos el final de la lista.
  printf("----------------------------------\n");
}

/**
 * Mostrar Tabla de Marco de Páginas
 * Función que imprime a la salida estándar el contenido de la RAM (marcos de página).
 * @param marco_de_pagina_inicial El marco de página inicial para iterar sobre la lista ligada.
 * @return void
 */
void mostrar_tabla_de_marcos_de_pagina(MarcoPagina *marco_de_pagina_inicial)
{
  // Variables locales.
  MarcoPagina *actual = marco_de_pagina_inicial; // Para iterar por los marcos de página.

  // Imprimimos el encabezado.
  printf("Tabla de Marcos de Página:\n\n");
  printf("----------------------------------\n");
  printf("| ID Marco de Página | ID Página |\n");
  printf("----------------------------------\n");

  // Iteramos hasta recorrer toda la lista.
  while (actual != NULL)
  {
    // Imprimimos el registro actual.
    printf("| %18i | %9i |\n", actual->id_marco, actual->id_pagina);

    // Avanzamos en la lista ligada.
    actual = actual->siguiente;
  }

  // Imprimimos el final de la lista.
  printf("----------------------------------\n");
}

/**
 * Buscar Página en RAM
 * Realiza una búsqueda dentro de la RAM para verificar si la página especificada ya está
 * cargada, en caso de encontrarla devuelve el Marco de Página correspondiente y NULL en 
 * caso contrario.
 * @param id_pagina_a_buscar El ID de la página a buscar en la RAM.
 * @return El Marco de Página dónde se encontró la página o NULL en caso de que no se haya encontrado.
 */
MarcoPagina *buscar_pagina_en_ram(int id_pagina_a_buscar, MarcoPagina *marco_pagina_inicial)
{
  // Variables locales.
  MarcoPagina *actual = marco_pagina_inicial;

  // Realizamos la búsqueda.
  while (actual != NULL)
  {
    // Verificamos si el ID es el que buscamos.
    if (id_pagina_a_buscar == actual->id_pagina)
    {
      return actual;
    }

    // Nos movemos al siguiente elemento.
    actual = actual->siguiente;
  }

  // No se encontró el ID especificado, devolvemos NULL.
  return NULL;
}

void insertar_en_ram(int id_pagina_a_insertar, MarcoPagina **marco_de_pagina_inicial)
{
  // Variables locales.
  MarcoPagina *temporal,                                    // Variable temporal para operaciones varias.
      *nuevo_marco_de_pagina = malloc(sizeof(MarcoPagina)); // Variable para almacenar el nuevo marco de página.
  int contador;                                             // Variable para contar el número de elementos en la RAM actualmente.

  // Siempre será nulo el siguiente elemento porque es FIFO.
  nuevo_marco_de_pagina->siguiente = NULL;

  // Siempre el nuevo marco de página tendrá la página a insertar.
  nuevo_marco_de_pagina->id_pagina = id_pagina_a_insertar;

  // Verificamos que no exista la página solicitada en la RAM.
  temporal = buscar_pagina_en_ram(id_pagina_a_insertar, *marco_de_pagina_inicial);

  if (temporal != NULL)
  {
    // La página ya se encuentra en RAM, abortamos la ejecución.
    return;
  }

  // Calculamos el número de páginas actualmente en la RAM.
  contador = 0;
  temporal = *marco_de_pagina_inicial;

  while (temporal != NULL)
  {
    // Aumentamos el contador.
    contador++;
    // Nos movemos al siguiente elemento.
    temporal = temporal->siguiente;
  }

  // Si hay espacio suficiente, insertamos.
  if (contador < NUM_PAGINAS_MARCO)
  {
    // Creamos el nuevo marco de página.
    nuevo_marco_de_pagina->id_marco = contador;
    nuevo_marco_de_pagina->id_pagina = id_pagina_a_insertar;

    // Verificamos si la RAM está vacía.
    if (contador == 0)
    {
      // En caso de que sea vacío, la página actual será lo primero que carguemso en RAM.
      (*marco_de_pagina_inicial) = nuevo_marco_de_pagina;
    }
    else
    {
      // Añadimos el nuevo marco de página al final de la lista ligada.
      temporal = *marco_de_pagina_inicial;
      while (temporal->siguiente != NULL)
      {
        temporal = temporal->siguiente;
      }
      temporal->siguiente = nuevo_marco_de_pagina;
    }
  }
  // Si no hay espacio suficiente, algoritmo de fallo de página.
  else
  {
    // Asignamos el ID del marco de página existente en FIFO al nuevo elemento.
    nuevo_marco_de_pagina->id_marco = (*marco_de_pagina_inicial)->id_marco;

    // Recorremos la lista en un elemento.
    (*marco_de_pagina_inicial) = (*marco_de_pagina_inicial)->siguiente;

    // Iteramos para encontrar el último elemento en la lista.
    temporal = (*marco_de_pagina_inicial);
    while (temporal->siguiente != NULL)
    {
      temporal = temporal->siguiente;
    }

    // Insertamos el nuevo marco de página al final.
    temporal->siguiente = nuevo_marco_de_pagina;
  }
}