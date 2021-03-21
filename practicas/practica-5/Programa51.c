/**
 * Programa51.c. Realizar un programa que inicie un hilo principal que a su vez crea dos hilos. El hilo
 * principal espera hasta que ambos hilos terminen y después finaliza. Los hilos sólo deben de mostrar algún
 * mensaje en pantalla y terminar.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Prototipos de funciones.
void *fun_hilo_principal();
void *fun_hilo_secundario(void *);

// Función principal.
int main(int argc, char const *argv[])
{
  // Variables locales.
  pthread_t hilo_principal;

  // Creamos el hilo principal.
  pthread_create(&hilo_principal, NULL, fun_hilo_principal, NULL);

  // Esperamos la finalización del hilo principal.
  pthread_join(hilo_principal, NULL);

  // Exit status = 0.
  return 0;
}

/**
 * Hilo Principal
 * Esta función contiene la definición de la operación del hilo principal de
 * la aplicación.
 */
void *fun_hilo_principal()
{
  // Variables locales.
  pthread_t hilo_secundario_1, hilo_secundario_2;

  // Mostramos un mensaje.
  printf("Mensaje desde Hilo Principal\n");

  // Creamos los dos hilos secundarios.
  pthread_create(&hilo_secundario_1, NULL, fun_hilo_secundario, (void *)1);
  pthread_create(&hilo_secundario_2, NULL, fun_hilo_secundario, (void *)2);

  // Esperamos a que finalicen ambos hilos secundarios.
  pthread_join(hilo_secundario_1, NULL);
  pthread_join(hilo_secundario_2, NULL);

  // Regresamos un valor cero.
  return 0;
}

/**
 * Hilo Secundario
 * Esta función contiene la definición de la operación de un hilo secundario
 * de la aplicación.
 */
void *fun_hilo_secundario(void *numero_parametro)
{
  // Variables locales.
  int numero_hilo = (int)numero_parametro;

  // Mostramos un mensaje.
  printf("Mensaje desde hilo secundario #%i\n", numero_hilo);

  // Regresamos un valor cero.
  return 0;
}
