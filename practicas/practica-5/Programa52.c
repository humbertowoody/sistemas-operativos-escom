/**
 * Programa52.c. Realizar un programa con una variable entera global (fuera de main()) con un valor inicial
 * de cero. Crear un hilo que incremente la variable global en a unidades y crear otro hilo que la disminuya en
 * b unidades. Al final el hilo principal imprimará el valor de la variable global.
 */
#include <stdio.h>
#include <pthread.h>

// Prototipos funciones
void *fun_aumentar_a(void *);
void *fun_disminuir_b(void *);

// Variables globales.
int variable_global = 0;

// Función principal
int main(int argc, char const *argv[])
{
  // Variables locales.
  int a,                   // Para almacenar el número de unidades a aumentar.
      b;                   // Para almacenar el número de unidades a disminuir.
  pthread_t hilo_aumentar, // El hilo para aumentar la variable global.
      hilo_disminuir;      // El hilo para disminuir la variable global.

  // Leemos los valores de a y b.
  printf("Ingrese el número de unidades para aumentar (a): ");
  scanf("%i", &a);
  printf("Ingrese el número de unidades para disminuir (b): ");
  scanf("%i", &b);

  // Creamos los hilos.
  pthread_create(&hilo_aumentar, NULL, fun_aumentar_a, (void *)a);
  pthread_create(&hilo_disminuir, NULL, fun_disminuir_b, (void *)b);

  // Esperamos la finalización de ambos hilos.
  pthread_join(hilo_aumentar, NULL);
  pthread_join(hilo_disminuir, NULL);

  // Mostramos el valor de la variable global.
  printf("La variable global vale: %i\n", variable_global);

  // Exit status = 0.
  return 0;
}

/**
 * Función Aumentar A
 * Función que aumenta en a unidades el valor de la variable global.
 * @param parametro_original Una variable de tipo (void*) que contenga el valor de a.
 * @return void*
 */
void *fun_aumentar_a(void *parametro_original)
{
  // Variables locales.
  int a = (int)parametro_original;

  // Realizamos la operación.
  variable_global += a;

  // Finalizamos la ejecución del hilo
  return 0;
}

/**
 * Función Disminuir B
 * Función que disminuye en b unidades el valor de la variable global.
 * @param parametro_original Una variable de tipo (void*) que contenga el valor de b.
 * @return void*
 */
void *fun_disminuir_b(void *parametro_original)
{
  // Variables locales.
  int b = (int)parametro_original;

  // Realizamos la operación.
  variable_global -= b;

  // Finalizamos la ejecución del hilo
  return 0;
}
