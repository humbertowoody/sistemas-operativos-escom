/**
 * Programa33.c Realice un programa que cree cinco procesos. Cada uno de estos procesos escribirá en un
 * archivo sólo una palabra de la siguiente oración: “Hola esta es mi práctica uno”. El proceso padre se
 * encargará de escribir la última palabra (uno).
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// Constantes de operación.
#define NOMBRE_ARCHIVO "salida-programa33.txt"

// Prototipos de funciones.
void crear_hijo(char *, FILE *); // Crea un proceso hijo.

// Función principal.
int main(int argc, char const *argv[])
{
  // Variables locales.
  FILE *archivo = fopen(NOMBRE_ARCHIVO, "a"); // Abrimos el archivo en modo "append" (anexar)

  // Hilo hijo para la palabra "hola".
  crear_hijo("Hola", archivo);
  wait(NULL);

  // Hilo hijo para la palabra "esta".
  crear_hijo("esta", archivo);
  wait(NULL);

  // Hilo hijo para la palabra "es".
  crear_hijo("es", archivo);
  wait(NULL);

  // Hilo hijo para la palabra "mi".
  crear_hijo("mi", archivo);
  wait(NULL);

  // Hilo hijo para la palabra "práctica".
  crear_hijo("práctica", archivo);
  wait(NULL);

  // Imprimimos la frase final ("uno") al archivo.
  fprintf(archivo, "%s.\n", "uno");

  // Cerramos el archivo.
  fclose(archivo);

  // Exit status = 0.
  return 0;
}

/**
 * Crear Hijo
 * Función que crea un proceso hijo y adjunta la frase al final
 * del archivo.
 * @param frase La frase a incluir en el archivo.
 * @param archivo Un apuntador de tipo FILE al archivo para realizar la escritura.
 * @return void
 */
void crear_hijo(char *frase, FILE *archivo)
{
  // Creamos el proceso hijo.
  if (fork() == 0)
  {
    // Imprimimos la frase en el archivo.
    fprintf(archivo, "%s ", frase);

    // Finalizamos la ejecución del hijo.
    exit(0);
  }
}