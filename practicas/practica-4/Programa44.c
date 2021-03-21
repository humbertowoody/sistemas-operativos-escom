/**
 * Programa44.c. Programe el Algoritmo de Dekker en dos procesos no emparentados, utilizando memoria
 * compartida ejecutándolos en terminales diferentes.
 */
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>

// Constantes de operación.
#define NOMBRE_LLAVE "llave-programa44"
#define ID_PROYECTO 'k'
#define TRUE 1
#define FALSE 0

// Estructura para almacenar el estado del algoritmo de Dekker.
typedef struct estado_dekker
{
  int p1_desea_entrar;
  int p2_desea_entrar;
  int proceso_favorecido;
} estado_dekker;

// Prototipos de funciones.

// Función principal.
int main(int argc, char **argv)
{
  // Variables locales.
  key_t llave;
  int shmid,
      id_proceso;
  estado_dekker *estado;

  // Creamos la llave.
  llave = ftok(NOMBRE_LLAVE, ID_PROYECTO);

  // Obtenemos el ID de la memoria compartida.
  shmid = shmget(llave, sizeof(estado_dekker), IPC_CREAT | 0600);

  // Nos adjuntamos a la memoria compartida.
  estado = shmat(shmid, 0, 0);

  // Instrucción para limpiar la mmoria compartida.
  // shmdt(&estado);
  // shmctl(shmid, IPC_RMID, 0);
  // if ('a' == 'a')
  // {
  //   return -1;
  // }

  // Preguntamos al usuario que nos indique cuál id de proceso somos.
  do
  {
    printf("Ingresa ID de proceso [1|2]: ");
    scanf("%i", &id_proceso);
  } while (id_proceso != 1 && id_proceso != 2); // Validación de entrada.

  // Ejecutamos esto indefinidamente.
  while (TRUE)
  {
    // Determinamos flujo en función del proceso seleccionado.
    if (id_proceso == 1)
    {
      // Iniciamos.
      estado->p1_desea_entrar = TRUE;

      // Esperamos a que se desocupe.
      while (estado->p2_desea_entrar)
      {
        if (estado->proceso_favorecido == 2)
        {
          // Ya no deseamos entrar.
          estado->p1_desea_entrar = FALSE;

          // Esperamos.
          while (estado->proceso_favorecido == 2)
            ;

          // Ahora volvemos a desear entrar.
          estado->p1_desea_entrar = TRUE;
        }
        // Sección crítica proceso 1
        printf("Sección crítica proceso 1\n");
        // sleep(1);

        // Favorecemos al proceso 2
        estado->proceso_favorecido = 2;

        // Ya no deseamos entrar.
        estado->p1_desea_entrar = FALSE;

        // Otras tareas.
      }
    }
    else
    {
      // Iniciamos.
      estado->p2_desea_entrar = TRUE;

      // Esperamos a que se desocupe.
      while (estado->p1_desea_entrar)
      {
        if (estado->proceso_favorecido == 1)
        {
          // Ya no deseamos entrar.
          estado->p2_desea_entrar = FALSE;

          // Esperamos.
          while (estado->proceso_favorecido == 1)
            ;

          // Ahora volvemos a desear entrar.
          estado->p2_desea_entrar = TRUE;
        }
        // Sección crítica proceso 2
        printf("Sección crítica proceso 2\n");
        // sleep(1);

        // Favorecemos al proceso 1.
        estado->proceso_favorecido = 1;

        // Ya no deseamos entrar.
        estado->p2_desea_entrar = FALSE;

        // Otras tareas.
      }
    }
  }

  return 0;
}