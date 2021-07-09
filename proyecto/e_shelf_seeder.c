/**
 * seeder.c
 * 
 * Este archivo sirve para llenar, de forma inicial, la base de datos utilizada por E-Shelf para un demo de funcionamiento.
 */
#include <stdlib.h>  // Para operaciones y definiciones de tipo estándar.
#include <stdio.h>   // Para operaciones de entrada y salida estándar.
#include <string.h>  // Para operaciones con cadenas de caracteres.
#include "archivo.h" // Para guardar los datos en los archivos correspondientes.

// Constantes de operación
#define PARAM_CLIENTES "--clientes"
#define PARAM_LIBROS "--libros"
#define PARAM_PROVEEDORES "--proveedores"
#define PARAM_CARRITOS "--carritos"
#define PARAM_TODO "--todo"

// Prototipos de funciones.
void generar_clientes();    // Para generar clientes default de E-Shelf.
void generar_libros();      // Para generar libros default en E-Shelf.
void generar_proveedores(); // Para generar proveedores default en E-Shelf.
void generar_carritos();    // Para generar carritos default en E-Shelf.

// Función principal.
int main(int argc, char *argv[])
{
  // Verificamos el número de argumentos.
  if (argc < 2)
  {
    // Mostramos menú.
    printf("E-Shelf: Seeding inicial de la base de datos.\n\n");
    printf("Descripción: Este programa permite generar los datos iniciales para un demo funcional de E-Shelf.\n");
    printf("Funcionamiento:\n");
    printf("\t%s [PARAMETRO_1] [PARAMETRO_2] [...]\n", argv[0]);
    printf("Parámetros disponibles:\n");
    printf("\t%s Genera clientes default en E-Shelf.\n", PARAM_CLIENTES);
    printf("\t%s Genera proveedores default en E-Shelf.\n", PARAM_PROVEEDORES);
    printf("\t%s Genera carritos default en E-Shelf.\n", PARAM_CARRITOS);
    printf("\t%s Genera libros default en E-Shelf.\n", PARAM_LIBROS);
    printf("\t%s Genera todas las opciones anteriores en E-Shelf.\n", PARAM_TODO);
    printf("\nE-Shelf | Sistemas Operativos ESCOM, 2021.\n\n");
  }
  else
  {
    // Iteramos sobre cada argumento y realizamos la operación especificada.
    for (int argumento_actual = 1; argumento_actual < argc; argumento_actual++)
    {
      // Seleccionamos la opción adecuada.
      if (strcmp(argv[argumento_actual], PARAM_CARRITOS) == 0)
      {
        printf("Generando carritos...\n");
        generar_carritos();
        printf("¡Carritos generados!\n");
      }
      else if (strcmp(argv[argumento_actual], PARAM_CLIENTES) == 0)
      {
        printf("Generando clientes...\n");
        generar_clientes();
        printf("Clientes generados!\n");
      }
      else if (strcmp(argv[argumento_actual], PARAM_LIBROS) == 0)
      {
        printf("Generando libros...\n");
        generar_libros();
        printf("¡Libros generados!\n");
      }
      else if (strcmp(argv[argumento_actual], PARAM_PROVEEDORES) == 0)
      {
        printf("Generando proveedores...\n");
        generar_proveedores();
        printf("¡Proveedores generados!\n");
      }
      else if (strcmp(argv[argumento_actual], PARAM_TODO) == 0)
      {
        printf("Generando clientes...\n");
        generar_clientes();
        printf("Clientes generados!\n");
        printf("Generando proveedores...\n");
        generar_proveedores();
        printf("¡Proveedores generados!\n");
        printf("Generando libros...\n");
        generar_libros();
        printf("¡Libros generados!\n");
        printf("Generando carritos...\n");
        generar_carritos();
        printf("¡Carritos generados!\n");
      }
      else
      {
        // Si no reconocemos la opción, mostramos este mensaje.
        printf("ERROR: Parámetro \"%s\" no reconocido.\n", argv[argumento_actual]);
      }
    }
  }

  return 0;
}

/**
 * generar_clientes
 * Función que genera una serie de clientes predefinidos para el sistema E-Shelf y los almacena en disco.
 */
void generar_clientes()
{
  // Los clientes predefinidos a generar.
  cliente clientes[10] = {
      {1, "humberto@eshelf.com", "Humberto Alejandro", "Ortega", "Alcocer", 24, "LasAbejasMeDanMiedoEShelf5!"},
      {2, "chelito@eshelf.com", "Consuelo", "Sánchez", "Fuentes", 21, "LasAbejasMeDanMiedoEShelf5!"},
      {3, "ricardo@eshelf.com", "Ricardo", "Díaz", "Matus", 21, "LasAbejasMeDanMiedoEShelf5!"},
      {4, "efrain@eshelf.com", "Efraín", "Chávez", "Hernández", 21, "LasAbejasMeDanMiedoEShelf5!"},
      {5, "batman@eshelf.com", "Bruno", "Díaz", "Wayne", 42, "NananananaBatman!"},
      {6, "usuario1@gmail.com", "Juan", "Torres", "Pérez", 27, "1234"},
      {7, "usuario2@gmail.com", "Andrea", "Fortuna", "Miranda", 29, "1234"},
      {8, "usuario3@gmail.com", "Jorge", "Royero", "Fernández", 24, "1234"},
      {9, "usuario4@gmail.com", "Linus", "Torvalds", "Linux", 24, "NvidiaMyLove123!"},
      {10, "profesor@eshelf.com", "José Alfredo", "Jiménez", "Benítez", 21, "TodosMisAlumnosDelEquipo8Sacan10!"}};

  // Los guardamos en el archivo.
  escribir_clientes_en_archivo(clientes, 10);
}

/**
 * generar_libros
 * Función que se utiliza para generar libros predefinidos para el sistema E-Shelf y los almacena en disco.
 */
void generar_libros()
{
  // Los libros predefinidos a generar.
  libro libros[5] = {
      {"978867346325", "El Código Da Vinci", "El conservador del museo del Louvre aparece muerto en extrañas circunstancias. Junto a su cadáver ha aparecido un desconcertante mensaje cifrado.", "Dan Brown", "Booket", "spa", 2003, 89.50},
      {"8441532109", "Clean code", "Clean Code, o Código Limpio, es una filosofía de desarrollo de software que consiste en aplicar técnicas simples que facilitan la escritura y lectura de un código, volviéndolo más fácil de entender.", "Robert C. Martin", "Grupo Anaya Comercial", "spa", 2012, 700},
      {"9780613832106", "Fisica - Volumen 1", "Libro con las bases fundamentales para ciencias e ingeniería como: mediciones, mov. unidimensional, vectores, mov. bidimensional y tridimensional, entre otros temas importantes", "David Halliday, Robert Resnick", "Patria", "spa", 1993, 405.6},
      {"9788433998972", "Un verdor terrible", " Benjamín Labatut ha escrito un libro inclasiﬁcable y poderosamente seductor, que habla de descubrimientos fruto del azar, teorías que bordean la locura, búsquedas alquímicas del conocimiento y la exploración de los límites de lo desconocido.", "Benjamín Labatut", "Anagrama", "spa", 2020, 360},
      {"9786073173162", "Becoming. Mi Historia", "", "Plaza & Janes", "spa", 2018, 450.0}};

  // Los guardamos en el archivo.
  escribir_libros_en_archivo(libros, 5);
}

/**
 * generar_proveedores
 * Funicón que se utiliza para generar proveedores predefinidos para el sistema E-Shelf y los almacena en disco.
 */
void generar_proveedores()
{
  // Los proveedores predefinidos a generar.
  proveedor proveedores[3] = {
      {1, "ventas@ghandi.com.mx", "Ghandi de México S.A. de C.V.", "NoMeAgradanLosSotanos123"},
      {2, "ventas@elsotano.com.mx", "El Sótano Librería", "MuerteAGhandi"},
      {3, "ventas@libreriasmartinez.com.mx", "Librerías Martínez", "hola1234"}};

  // Los guardamos en el archivo.
  escribir_proveedores_en_archivo(proveedores, 3);
}

/**
 * generar_carritos
 * Función que se utiliza para generar carritos predefinidos para el sistema E-Shelf y los almacena en disco.
 */
void generar_carritos()
{
  // Los carritos predefinidos a generar.
  carrito carritos[2] = {{2, "9780613832106", 1},
                         {2, "9788433998972", 2}};

  // Los guardamos en el archivo correspondiente.
  escribir_carritos_en_archivo(carritos, 2);
}
