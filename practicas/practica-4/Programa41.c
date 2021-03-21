/**
 * Programa41.c Elabore un programa que tenga una variable con un valor inicial de cero. Posteriormente se
 * deben crear dos hilos independientes, uno de ellos incrementa permanentemente la variable en uno y el otro
 * la disminuya en uno. Después de n segundos el proceso debe imprimir el valor final de la variable y
 * terminar. El número de segundos que el proceso padre espera, se debe pasar en la línea de comandos.
 * Sincronice los hilos mediante el uso de semáforos.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <pthread.h>
#include <time.h>

// Constantes de operación.
#define PERMISOS 0644
#define NUMERO_SEGUNDOS_DEFAULT 10 // El número de segundos a utilizar por defecto.

// Prototipos de funciones.
int crea_semaforo(key_t, int);
void down(int);
void up(int);
void *reducir_variable(void *);
void *aumentar_variable(void *);

// Estructura para parámetros de las funciones dentro del hilo.
typedef struct
{
  int *var_comp;      // La variable compartida.
  int num_segs;       // El número de segundos a ejecutarse.
  int semaforo;       // El semáforo.
} parametros_funcion; // La definición de tipo de dato.

// Función principal.
int main(int argc, char const *argv[])
{
  // Variables locales.
  int numero_segundos,                       // El número de segundos para esperar.
      variable_compartida = 0,               // La variable compartida.
      *ptr_variable_compartida,              // Un apuntador a la variable compartida.
      semaforo,                              // El semáforo.
      shmid,                                 // El ID de SHM para IPC
      retorno1,                              // El valor de retorno del primer hilo.
      retorno2;                              // El valor de retorno del segundo hilo.
  key_t llave;                               // La llave de IPC
  pthread_t hilo1, hilo2;                    // Las variables para los hilos a crear.
  parametros_funcion *estructura_parametros; // La estructura con los parámetros para cada hilo.

  // Verificamos que el usuario haya proporcionado un numero de segundos a esperar.
  if (argc != 2)
  {
    numero_segundos = NUMERO_SEGUNDOS_DEFAULT;
  }
  else
  {
    // En lugar de realizar la conversión con `atoi` (que puede presentar problemas), usamos sscanf().
    sscanf(argv[1], "%i", &numero_segundos);
  }

  // Creamos la llave.
  llave = ftok("llave-programa41", 'k');

  // Creamos el semáforo.
  semaforo = crea_semaforo(llave, 1);

  // Verificamos la creación correcta del semáforo.
  if (semaforo == -1)
  {
    printf("Error creando el semáforo, intente de nuevo más tarde.\n");
    return -1;
  }

  // Asignamos el apuntador a la variable compartida.
  ptr_variable_compartida = &variable_compartida;

  // Creamos la estructura con los parámetros para la función.
  estructura_parametros = (parametros_funcion *)malloc(sizeof(parametros_funcion));
  estructura_parametros->var_comp = ptr_variable_compartida;
  estructura_parametros->num_segs = numero_segundos;
  estructura_parametros->semaforo = semaforo;

  // Mensaje.
  printf("Valor inicial de la variable compartida: %i\n", variable_compartida);

  // Creamos los dos hilos.
  retorno1 = pthread_create(&hilo1, NULL, aumentar_variable, (void *)estructura_parametros);
  retorno2 = pthread_create(&hilo2, NULL, reducir_variable, (void *)estructura_parametros);

  // Finalizamos los hilos.
  pthread_join(hilo1, NULL);
  pthread_join(hilo2, NULL);

  // Verificamos que se hayan finalizado correctamente la ejecución de los hilos.
  if (retorno1 != 0 || retorno2 != 0)
  {
    printf("Ha ocurrido un problema finalizando la ejecución de los hilos.\n");
    return -1;
  }

  // Mostramos un mensaje con el valor final de la variable.
  printf("El valor final de la variable compartida: %i\n", variable_compartida);

  // Exit status = 0.
  return 0;
}

/**
 * Reducir variable
 * Función que reduce el valor de la variable durante los segundos especificados.
 * @param parametros_originales La variable de tipo (void*) con los parámetros originales de la función.
 * @return Esta función no retorna ningún valor.
 */
void *reducir_variable(void *parametros_originales)
{
  // Variables locales.
  parametros_funcion *estructura_parametros = (parametros_funcion *)parametros_originales; // Convertimos los parámetros originales en la estructura que creamos.
  time_t inicio,                                                                           // Variable que almacena el tiempo inicial de ejecución.
      fin,                                                                                 // Variable que almacenará los tiempos finales.
      tiempo_transcurrido;                                                                 // Variable que almacenará el tiempo transcurrido de ejecución.

  // Inicializamos el conteo del tiempo.
  time(&inicio);
  time(&fin);
  tiempo_transcurrido = fin - inicio;

  // Realizamos la operación mientras el número de segundos transcurridos sea menores o iguales a los segundos especificados.
  while (tiempo_transcurrido <= ((double)estructura_parametros->num_segs))
  {
    // Operación P
    down(estructura_parametros->semaforo);

    // Restamos uno.
    (*estructura_parametros->var_comp)--;

    // Operacion V
    up(estructura_parametros->semaforo);

    // Tomamos la medida del tiempo actual.
    time(&fin);

    // Calculamos el tiempo transcurrido.
    tiempo_transcurrido = fin - inicio;
  }

  return 0;
}

/**
 * Aumentar Variable
 * Función que aumenta el valor de la variable durante los segundos especificados.
 * @param parametros_originales La variable de tipo (void*) con los parámetros originales de la función.
 * @return Esta función no retorna ningún valor.
 */
void *aumentar_variable(void *parametros_originales)
{
  // Variables locales.
  parametros_funcion *estructura_parametros = (parametros_funcion *)parametros_originales; // Convertimos los parámetros originales en la estructura que creamos.
  time_t inicio,                                                                           // Variable que almacena el tiempo inicial de ejecución.
      fin,                                                                                 // Variable que almacenará los tiempos finales.
      tiempo_transcurrido;                                                                 // Variable que almacenará el tiempo transcurrido de ejecución.

  // Inicializamos el conteo del tiempo.
  time(&inicio);
  time(&fin);
  tiempo_transcurrido = fin - inicio;

  // Realizamos la operación mientras el número de segundos transcurridos sean menores o iguales a los segundos especificados.
  while (tiempo_transcurrido <= estructura_parametros->num_segs)
  {
    // Operación P.
    down(estructura_parametros->semaforo);

    // Sumamos uno.
    (*estructura_parametros->var_comp)++;

    // Operación V.
    up(estructura_parametros->semaforo);

    // Tomamos la medida del tiempo actual.
    time(&fin);

    // Calculamos el tiempo transcurrido.
    tiempo_transcurrido = fin - inicio;
  }

  return 0;
}

/**
 * Crea Semáforo
 * Esta función crea un nuevo semáforo en función de una llave y el valor inicial proporcionado.
 * @param llave La llave para el IPC
 * @param valor_inicial El valor inicial para el semáforo.
 * @return El id del semáforo.
 */
int crea_semaforo(key_t llave, int valor_inicial)
{
  // Obtenemos el ID de nuestro nuevo semáforo.
  int semid = semget(llave, 1, IPC_CREAT | PERMISOS);

  // Verificamos la creación correcta del semáforo.
  if (semid == -1)
  {
    return -1;
  }

  // Asignamos el valor inicial.
  semctl(semid, 0, SETVAL, valor_inicial);

  // Regresamos el ID del semáforo creado.
  return semid;
}

/**
 * Down (Operación P)
 * Función que reduce el valor del semáforo en 1.
 * @param semid El ID del semáforo
 * @return void
 */
void down(int semid)
{
  // Estructura con la operación correspondiente.
  struct sembuf op_p[] = {0, -1, 0};

  // Realizamos la operación.
  semop(semid, op_p, 1);
}

/**
 * Up (Operación V)
 * Función que aumenta el valor del semáforo en 1.
 * @param semid El ID del semáforo
 * @return void
 */
void up(int semid)
{
  // Estructura con la operación correspondiente.
  struct sembuf op_v[] = {0, +1, 0};

  // Realizamos la operación.
  semop(semid, op_v, 1);
}
