/**
 * Programa45.c. Programe el problema de los filósofos utilizando semáforos y memoria compartida.
 */
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Constantes de operación.
#define NUMERO_FILOSOFOS 5
#define PENSANDO 2
#define HAMBRIENTO 1
#define COMIENDO 0

// Macros para operaciones.
#define IZQUIERDA (num_filosofo + 4) % NUMERO_FILOSOFOS
#define DERECHA (num_filosofo + 1) % NUMERO_FILOSOFOS

// Variables globales (memoria compartida)
int estado[NUMERO_FILOSOFOS];
int filosofos[NUMERO_FILOSOFOS];
sem_t mutex;
sem_t S[NUMERO_FILOSOFOS];

// Prototipos de funciones.
void probar(int);
void tomar_tenedor(int);
void dejar_tenedor(int);
void *filosofo(void *);

// Función principal.
int main(int argc, char *argv[])
{
  // Variables locales.
  int i;
  pthread_t hilo_filosofo[NUMERO_FILOSOFOS];

  // Inicializar los filósofos.
  for (i = 0; i < NUMERO_FILOSOFOS; i++)
  {
    filosofos[i] = i;
  }

  // Inicializar los semáforos.
  sem_init(&mutex, 0, 1);
  for (i = 0; i < NUMERO_FILOSOFOS; i++)
  {
    sem_init(&S[i], 0, 0);
  }

  // Creamos los hilos para cada filósofo.
  for (i = 0; i < NUMERO_FILOSOFOS; i++)
  {
    // Creamos el hilo.
    pthread_create(&hilo_filosofo[i], NULL, filosofo, &filosofos[i]);

    // Mostramos un mensaje con el estado inicial del filósofo, pensando.
    printf("El filósofo %i está pensando\n", i + 1);
  }

  // Esperamos a que finalicen los hilos.
  for (i = 0; i < NUMERO_FILOSOFOS; i++)
  {
    pthread_join(hilo_filosofo[i], NULL);
  }

  // Exit status = 0.
  return 0;
}

/**
 * Probar
 * Función que verifica si un filósofo puede comenzar a comer.
 * @param num_filosofo El ID del filósofo a verificar.
 * @return void
 */
void probar(int num_filosofo)
{
  // Verificamos si se cumplen las condiciones antes de avanzar.
  if (estado[num_filosofo] == HAMBRIENTO && estado[IZQUIERDA] != COMIENDO && estado[DERECHA] != COMIENDO)
  {
    // El filósofo puede comer.
    estado[num_filosofo] = COMIENDO;

    // Pausa de 3 segundos.
    sleep(3);

    // Mostramos un mensaje con los cubiertos tomados por el filósofo.
    printf("El filósofo %i toma el tenedor %i y %i\n", num_filosofo + 1, IZQUIERDA + 1, num_filosofo + 1);

    // Mostramos un mensaje con la acción del filósofo.
    printf("El filósofo %i está COMIENDO.\n", num_filosofo + 1);

    // Cambiamos el estado del semáforo.
    sem_post(&S[num_filosofo]);
  }
}

/**
 * Tomar Tenedor
 * Función que hace que un filósofo tome un tenedor, cambie su estado a hambriento,
 * verifica si le es posible al filósofo comer, y realiza la acción de ser posible.
 * En caso de que no pueda comer, deja su estado como hambriento y prosigue.
 * @param num_filosofo El ID del filósofo para realizar la operación.
 * @return void
 */
void tomar_tenedor(int num_filosofo)
{
  // Colocamos el semáforo en espera.
  sem_wait(&mutex);

  // Colocamos el estado del filósofo en: "hambriento"
  estado[num_filosofo] = HAMBRIENTO;

  // Imprimimos un mensaje con la información.
  printf("El filósofo %i está Hambriento\n");

  // Comemos si los vecinos del filósofo actual no están comiendo.
  probar(num_filosofo);

  // Actualizamos el valor del semáforo.
  sem_post(&mutex);

  // Si no pudo comer esperamos a que se indique su turno.
  sem_wait(&S[num_filosofo]);

  // Hacemos una pausa de un segundo.
  sleep(1);
}

/**
 * Dejar Tenedor
 * Función que realiza la simulación de un filósofo dejando sus cubiertos de vuelta en la mesa
 * después de haber comido, y se hace la prueba de que los dos filósofos colindantes puedan
 * comer.
 * @param num_filosofo El ID del filósofo para realizar la operación.
 * @return void
 */
void dejar_tenedor(int num_filosofo)
{
  // Cambiamos el estado del semáforo.
  sem_wait(&mutex);

  // Mostramos un mensaje con el filósofo dejando el tenedor.
  printf("El filósofo %i deja los tenedores %i y %i en la mesa\n", num_filosofo + 1, IZQUIERDA + 1, num_filosofo + 1);

  // Mostramos un mensaje con el nuevo estado del filósofo: pensando
  printf("El filósofo %i está pensando\n", num_filosofo + 1);

  // Probamos si el filósofo a nuestra izquierda puede comer.
  probar(IZQUIERDA);

  // Probamos si el filósofo a nuestra derecha puede comer.
  probar(DERECHA);

  // Cambiamos el estado del semáforo.
  sem_post(&mutex);
}

/**
 * Filósofo
 * Esta función representa el ciclo de ejecución de un filósofo, el cual consiste en:
 *   1) Tomar su cubiertos.
 *   2) Dejar sus cubiertos.
 * @param parametro_original Una variable de tipo (void*) que representa el ID del filósofo.
 * @return void
 */
void *filosofo(void *parametro_original)
{
  // Variables locales.
  int *id_filosofo = (int *)parametro_original;

  // Ciclo infinito.
  while (1)
  {
    // Esperamos un segundo.
    sleep(1);

    // Tomamos los cubiertos.
    tomar_tenedor(*id_filosofo);

    // Hacemos una pausa.
    sleep(0);

    // Devolvemos los cubiertos.
    dejar_tenedor(*id_filosofo);
  }
}
