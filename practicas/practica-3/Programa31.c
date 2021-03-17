/**
 * Programa31.c Realizar un programa que cree diez procesos hijos del mismo padre y cada uno muestre el
 * mensaje “Hola soy el proceso con pid XXXX y mi padre es XXXX” y el conteo del uno al diez. Al final el
 * padre espera a los hijos y termina.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// Constantes de operación.
#define NUM_PROCESOS_HIJOS 10

// Prototipos de funciones.
void imprimir_informacion(int, pid_t, pid_t);
void crear_hijo();

// Función principal.
int main()
{
  // Variables locales.
  pid_t id_proceso_hijo; // Para almacenar los PIDs de los hijos y esperarlos.

  // Información del padre.
  printf("Información del proceso padre:\n\n");
  imprimir_informacion(-1, getpid(), getppid());

  // Información de los procesos hijos.
  printf("\n\nInformación de los procesos hijos:\n\n");

  // Creamos 10 hijos.
  for (int i = 0; i < NUM_PROCESOS_HIJOS; i++)
  {
    crear_hijo(i + 1);
    wait(NULL);
  }

  // Fin de ejecución, exit status = 0.
  return 0;
}

/**
 * Crear un proceso hijo
 * Esta función crea un proceso hijo y muestra su información en la
 * salida estándar.
 * @return void
 */
void crear_hijo(int id_hijo)
{
  // Variables locales.
  int i;

  // Creamos el proceso hijo.
  if (fork() == 0)
  {
    // Mostramos su información.
    imprimir_informacion(id_hijo, getpid(), getppid());

    // Conteo del uno al diez.
    for (i = 0; i < 10; i++)
    {
      // Colocamos el id_hijo seguido del PID y el valor.
      printf("- %2i) [%5i]: %2i\n", id_hijo, getpid(), i + 1);
    }

    // Finalizamos la ejecución del proceso hijo con status = 0.
    exit(0);
  }
}

/**
 * Función para imprimir la información de un proceso
 * incluyendo su PID y el de su padre.
 * @param yo El pid_t con el PID del proceso actual.
 * @param padre El pid_t con el PID del proceso padre al actual.
 * @return void
 */
void imprimir_informacion(int id_hijo, pid_t yo, pid_t padre)
{
  printf("- %2i) Soy el proceso con PID: %d y mi padre es: %d\n", id_hijo, yo, padre);
}