/**
 * Programa32.c Realice un programa que cree un proceso hijo a partir de un proceso padre, el hijo creado a
 * su vez creará tres procesos hijos más. A su vez cada uno de los tres procesos creará dos procesos más. Cada
 * uno de los procesos creados imprimirá en pantalla el PID de su padre y su propio PID.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// Constantes de operación.
#define NUM_PROCESOS_HIJOS 1     // El número de procesos hijos que tendrá el padre.
#define NUM_PROCESOS_NIETOS 3    // El número de procesos nietos que tendrá cada hijo.
#define NUM_PROCESOS_SUBNIETOS 2 // El número de procesos subnietos que tendrá cada nieto.
#define FORMATO_BONITO 1         // 0 para formato con tabs, 1 para formato con tabs.

// Prototipos de funciones.
void imprimir_informacion(pid_t, pid_t); // Función que imprime el PID y el del padre de un proceso.
void crear_hijo();                       // Función que crea un proceso hijo, imprime sus datos y crea N procesos nietos.
void crear_nieto();                      // Función que crea un proceso nieto, imprime sus datos y crea N procesos subnietos.
void crear_subnieto();                   // Función que crea un proceso subnieto e imprime sus datos.

// Función principal.
int main(int argc, char const *argv[])
{
  // Mensaje inicial con PID inicial del proceso general.
  imprimir_informacion(getpid(), getppid());

  // Creamos N procesos hijos.
  for (int procesosHijos = 0; procesosHijos < NUM_PROCESOS_HIJOS; procesosHijos++)
  {
    // Creamos el hijo.
    crear_hijo();

    // Esperamos a que finalice la ejecución del hijo.
    wait(NULL);
  }

  // Exit status = 0.
  return 0;
}

/**
 * Crear Hijo
 * Función que crea un proceso hijo a partir del proceso actual.
 * @return void
 */
void crear_hijo()
{
  // Creamos el proceso hijo.
  if (fork() == 0)
  {
    // Mostramos su información.
    if (FORMATO_BONITO)
    {
      printf("\t");
    }
    imprimir_informacion(getpid(), getppid());

    // Creamos N procesos nietos.
    for (int procesosNietos = 0; procesosNietos < NUM_PROCESOS_NIETOS; procesosNietos++)
    {
      // Creamos el nieto.
      crear_nieto();

      // Esperamos a que finalice la ejecución del nieto.
      wait(NULL);
    }

    // Salimos del proceso.
    exit(0);
  }
}

/**
 * Crear Nieto
 * Función que crea un proceso nieto a partir de un proceso hijo.
 * @return void
 */
void crear_nieto()
{
  // Creamos el proceso nieto.
  if (fork() == 0)
  {
    // Mostramos la información del nieto.
    if (FORMATO_BONITO)
    {
      printf("\t\t");
    }
    imprimir_informacion(getpid(), getppid());

    // Creamos N procesos subnietos.
    for (int procesosSubnietos = 0; procesosSubnietos < NUM_PROCESOS_SUBNIETOS; procesosSubnietos++)
    {
      // Creamos el subnieto.
      crear_subnieto();

      // Esperamos a que finalice la ejecución del subnieto.
      wait(NULL);
    }

    // Finalizamos la ejecución.
    exit(0);
  }
}

/**
 * Crear Subnieto
 * Función que crea un proceso subnieto a partir de un proceso nieto.
 * @return void
 */
void crear_subnieto()
{
  // Creamos el proceso nieto.
  if (fork() == 0)
  {
    // Mostramos la información del nieto.
    if (FORMATO_BONITO)
    {
      printf("\t\t\t");
    }
    imprimir_informacion(getpid(), getppid());

    // Finalizamos la ejecución.
    exit(0);
  }
}

/**
 * Imprimir Información
 * Función para imprimir el PID y el de su padre de un
 * proceso particular.
 * @param yo El pid_t con el PID del proceso actual.
 * @param padre El pid_t con el PID del proceso padre.
 * @return void
 */
void imprimir_informacion(pid_t yo, pid_t padre)
{
  printf("Soy el proceso con PID: %i y mi padre es %i\n", yo, padre);
}
