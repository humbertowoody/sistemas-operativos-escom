/**
 * Programa53.c. Realizar un programa cree un proceso hijo que a su vez creará tres hilos. Cada uno de los
 * tres hilos creará dos hilos más. Cada uno de los hilos creados imprimirá en pantalla sus identificadores.
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// Prototipos de funciones
void *fun_hilo_primer_nivel();
void *fun_hilo_segundo_nivel();
void proceso_hijo();

// Función principal
int main(int argc, char const *argv[])
{
  // Creamos el proceso hijo.
  proceso_hijo();

  // Esperamos a que finalice su ejecución.
  wait(NULL);

  // Exit status = 0.
  return 0;
}

/**
 * Proceso Hijo
 * Función que define el comportamiento del proceso hijo que será
 * creado.
 */
void proceso_hijo()
{
  // Variables locales.
  pthread_t hilo_1, hilo_2, hilo_3; // Variables para los hilos a crear.

  // Creamos el proceso hijo.
  if (fork() == 0)
  {
    // Creamos tres hilos de primer nivel.
    pthread_create(&hilo_1, NULL, fun_hilo_primer_nivel, NULL);
    pthread_create(&hilo_2, NULL, fun_hilo_primer_nivel, NULL);
    pthread_create(&hilo_3, NULL, fun_hilo_primer_nivel, NULL);

    // Esperamos la ejecución de los hilos.
    pthread_join(hilo_1, NULL);
    pthread_join(hilo_2, NULL);
    pthread_join(hilo_3, NULL);

    // Finalizamos la ejecución del proceso hijo.
    exit(0);
  }
}

/**
 * Función Hilo de Primer Nivel
 * Esta función describe el comportamiento de los hilos de primer nivel.
 */
void *fun_hilo_primer_nivel()
{
  // Variables locales.
  pthread_t sub_hilo_1, sub_hilo_2; // Variables para los hilos a crear.

  // Mostramos un mensaje con el ID del hilo.
  printf("Soy un hilo de primer nivel con mi ID: %i\n", (int)pthread_self());

  // Creamos los hilos correspondientes.
  pthread_create(&sub_hilo_1, NULL, fun_hilo_segundo_nivel, NULL);
  pthread_create(&sub_hilo_1, NULL, fun_hilo_segundo_nivel, NULL);

  // Esperamos la finalización de la ejecución de los sub-hilos.
  pthread_join(sub_hilo_1, NULL);
  pthread_join(sub_hilo_2, NULL);

  // Finalizamos la ejecución del hilo de primer nivel.
  return 0;
}

/**
 * Función Hilo de Segundo Nivel.
 * Esta funciñon describe el comportamiento de los hilos de segundo nivel.
 */
void *fun_hilo_segundo_nivel()
{
  // Mostramos un mensaje con el ID del hilo.
  printf("Soy un hilo de segundo nivel con mi ID: %i\n", (int)pthread_self());

  // Finalizamos la ejecucion del hilo de segundo nivel.
  return 0;
}
