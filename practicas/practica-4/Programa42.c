/*
 * Programa42.c. Realizar un programa que utilice memoria compartida donde un proceso padre crea un
 * arreglo con tipos de dato float de 10 posiciones y lo comparte con un proceso hijo. El proceso hijo genera
 * 10 números aleatorios de tipo float y los guarda en el arreglo compartido. Al final el proceso padre muestra
 * los números que grabó el proceso hijo en el arreglo.
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

// Prototipos de funciones.
void proceso_hijo(float *);
void imprimir_arreglo(float *);

// Función principal
int main(int argc, char const *argv[])
{
  // Variables locales.
  int shmid,
      posicion;
  float *arreglo;
  key_t llave;
  pid_t pid;

  // Creamos la llave.
  llave = ftok("llave-programa42", 'k');

  // Obtenemos el ID
  shmid = shmget(llave, sizeof(float) * 10, IPC_CREAT | 0600);

  // Asignamos la variable.
  arreglo = shmat(shmid, 0, 0);

  // Usamos el tiempo actual como semilla para los números aleatorios.
  srand(time(0));

  // Creamos el proceso hijo con la memoria compartida.
  proceso_hijo(arreglo);

  // Esperamos a que finalice su ejecución.
  wait(NULL);

  // Mostramos los contenidos del arreglo.
  printf("Contenidos del arreglo:\n");
  imprimir_arreglo(arreglo);

  shmdt(&arreglo);

  shmctl(shmid, IPC_RMID, 0);

  // Exit status = 0;
  return 0;
}

/**
 * Proceso Hijo
 * Función que contiene la implementación del proceso hijo.
 * @param arreglo El arreglo de números flotantes para rellenar.
 * @return Esta función no regresa nada.
 */
void proceso_hijo(float *arreglo)
{
  // Variables locales.
  int posicion; // Variable para la posioción en la iteración del arreglo.

  // Creamos el subproceso.
  if (fork() == 0)
  {

    // Rellenamos el arreglo compartido.
    for (posicion = 0; posicion < 10; posicion++)
    {
      // Valor aleatorio.
      arreglo[posicion] = rand() + posicion;
    }

    // Finalizamos la ejecución del proceso.
    exit(0);
  }
}

/**
 * Imprimir Arreglo
 * Imprime el arreglo en la terminal.
 * @param arreglo Un arreglo de números flotantes.
 * @return void
 */
void imprimir_arreglo(float *arreglo)
{
  // Variables locales.
  int posicion;

  // Imprimimos mensaje inicial.
  printf("\t[ ");

  // Iteramos para cada elemento.
  for (posicion = 0; posicion < 10; posicion++)
  {
    printf("%.2f ", arreglo[posicion]);
  }

  // Cerramos el mensaje.
  printf("]\n\n");
}