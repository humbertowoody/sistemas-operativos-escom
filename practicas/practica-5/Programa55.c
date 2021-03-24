/**
 * Programa55.c. Realizar un programa donde un hilo se encargará de decir si un número entero dado por el
 * usuario es compuesto, si lo es, otro hilo se encargará de descomponerlo en sus números primos, si no lo es,
 * otro hilo se encargará de decir que si es primo.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Constantes de operación
#define MAX_FACTORES_PRIMOS 512 // Un valor razonable...

// Estructura para los resultados de la operación de descomposición en factores primos.
typedef struct resultados_descomposicion_primos
{
  int numeros[MAX_FACTORES_PRIMOS];
  int cantidad_numeros;
} resultados_descomposicion_primos;

// Prototipos de funciones
void *func_hilo_es_compuesto(void *);          // Función para ejecución de un hilo que determina si un número es compuesto.
void *func_hilo_descomponer_en_primos(void *); // Función para ejecución de un hilo que descompone un número en sus factores primos.
void *func_hilo_mensaje_es_primo(void *);      // Función para ejecución de un hilo que muestra el mensaje: "El número X es primo."

// Función principal.
int main(int argc, char *argv[])
{
  // Variables locales.
  int numero,
      iterador;
  resultados_descomposicion_primos *resultados_desc_primos;
  pthread_t hilo_descomponer_en_primos,
      hilo_mensaje_es_primo,
      hilo_es_compuesto;
  void *resultado_es_compuesto,
      *resultado_desc_primos_original;

  // Leer número del usuario.
  printf("Introduzca un número entero: ");
  scanf("%i", &numero);

  // Creamos el hilo que verifica si un número es compuesto.
  pthread_create(&hilo_es_compuesto, NULL, func_hilo_es_compuesto, (void *)numero);

  // Esperamos que finalice la ejecución del hilo.
  pthread_join(hilo_es_compuesto, &resultado_es_compuesto);

  // Verificamos el tipo de número.
  if (((int)resultado_es_compuesto) == 0)
  {
    // El número no es compuesto, creamos el hilo para mostrar el mensaje correspondiente.
    pthread_create(&hilo_mensaje_es_primo, NULL, func_hilo_mensaje_es_primo, (void *)numero);

    // Esperamos la finalización del hilo
    pthread_join(hilo_mensaje_es_primo, NULL);
  }
  else
  {
    // El número es compuesto, creamos el hilo para descomponerlo en sus factores primos.
    pthread_create(&hilo_descomponer_en_primos, NULL, func_hilo_descomponer_en_primos, (void *)numero);

    // Esperamos la finalización de la ejecución del hilo.
    pthread_join(hilo_descomponer_en_primos, &resultado_desc_primos_original);

    // Obtenemos la estructura con los resultados.
    resultados_desc_primos = (resultados_descomposicion_primos *)resultado_desc_primos_original;

    // Imprimimos los resultados.
    printf("El número %i es compuesto y estos son sus factores primos:\n", numero);

    for (iterador = 0; iterador < resultados_desc_primos->cantidad_numeros; iterador++)
    {
      printf("%i", resultados_desc_primos->numeros[iterador]);

      if ((iterador + 1) < resultados_desc_primos->cantidad_numeros)
      {
        printf(" * ");
      }
    }
    printf("\n");
  }

  // Exit status = 0.
  return 0;
}

/**
 * Función de Hilo: Descomponer en Primos
 * Esta función corresponde a la ejecución de un hilo que descompone un número entero en sus factores primos.
 * @param parametro_original El parámetro original de tipo (void*) que contiene un entero con el número proporcionado por el usuario.
 * @return Un valor de tipo (void*) que contiene una estructura de tipo resultados_descomposicion_primos.
 */
void *func_hilo_descomponer_en_primos(void *parametro_original)
{
  // Variables locales.
  int numero_original = (int)parametro_original, // El número original proporcionado por el usuario.
      iterador;                                  // Un iterador para descomponer el número en sus factores primos.
  resultados_descomposicion_primos *resultados;  // La estructura donde almacenaremos el resultado.

  // Asignamos la memoria necesaria para la estructura de resultados.
  resultados = malloc(sizeof(resultados_descomposicion_primos));

  // Inicializamos la cantidad de números primos hayados en 0.
  resultados->cantidad_numeros = 0;

  // Algoritmo para calcular los factores primos de un número entero.
  // Fuente: https://es.wikipedia.org/wiki/Factor_primo
  for (iterador = 2; numero_original > 1; iterador++)
  {
    while (numero_original % iterador == 0)
    {
      // Almacenamos en el arreglo el valor del iterador.
      resultados->numeros[resultados->cantidad_numeros] = iterador;

      // Aumentamos la cantidad de números.
      resultados->cantidad_numeros++;

      // Dividimos el número entre el iterador.
      numero_original /= iterador;
    }
  }

  // Regresamos la estructura con resultados.
  return (void *)resultados;
}

/**
 * Función de Hilo: Es Compuesto
 * Esta función corresponde a la ejecución de un hilo que determina si un número es compuesto o no.
 * @param parametro_original El parámetro original de tipo (void*) que contiene un entero con el número proporcionado por el usuario.
 * @return Un valor de tipo (void*) que contiene un entero 0 si NO es compuesto y 1 si SI es compuesto.
 */
void *func_hilo_es_compuesto(void *parametro_original)
{
  // Variables locales.
  int numero_original = (int)parametro_original,
      iterador;

  // Iteramos desde 2 hasta n-1
  for (iterador = 2; iterador < numero_original; iterador++)
  {
    // Si el actual iterador es divisor del número original, entonces es compuesto.
    if (numero_original % iterador == 0)
    {
      // Es un número compuesto.
      return (void *)1;
    }
  }

  // En este punto no encontramos un divisor, por lo que no es compuesto.
  return (void *)0;
}

/**
 * Función de Hilo: Mensaje: "Es Primo"
 * Esta función corresponde a la ejecución de un hilo que imprime en consola el mensaje: "El número X es primo.".
 * @param parametro_original El parámetro original de tipo (void*) que contiene un entero con el número proporcionado por el usuario.
 * @return void
 */
void *func_hilo_mensaje_es_primo(void *parametro_original)
{
  // Variables locales.
  int numero_original = (int)parametro_original;

  // Impresión del mensaje.
  printf("El número %i es primo.\n", numero_original);

  // Regresamos cero para finalizar la ejecución.
  return 0;
}
