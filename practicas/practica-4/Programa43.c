/**
 * Programa43.c. Crear una comunicación bidireccional (chat) entre dos procesos que no tengan ancestros en
 * común por medio de colas de mensajes.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

// Constantes de operación.
#define NOMBRE_LLAVE "llave-programa43"
#define ID_PROYECTO 'M'
#define PERMISOS 0660
#define TAM_NOMBRE 20
#define TAM_BUFFER_MENSAJES 255
#define MENU_SALIR "SALIR"

// Estructura para los mensajes.
typedef struct mensaje
{
  long message_type;                // El tipo de mensaje.
  char buffer[TAM_BUFFER_MENSAJES]; // El buffer de mensajes.
} mensaje;

// Prototipos de funciones.
void *imprimir_mensajes(void *); // Función para el hilo que escucha mensajes.

// Función principal.
int main(int argc, char **argv)
{
  key_t llave_cola_mensajes;
  int id_cola,
      opcion_menu;
  mensaje mensaje_a_enviar;
  pthread_t hilo_escucha;

  // Mensaje inicial.
  printf("Programa de Chat usando Colas de Mensajes de System V\n\n");

  // Obtenemos la llave de la cola de mensajes.
  llave_cola_mensajes = ftok(NOMBRE_LLAVE, ID_PROYECTO);

  // Obtenemos el ID de la cola si ya existe, en otro caso la creamos.
  if ((id_cola = msgget(llave_cola_mensajes, 0)) == -1)
  {
    printf("La cola no existe, creándola.\n");
    id_cola = msgget(llave_cola_mensajes, IPC_CREAT | PERMISOS);
  }
  else
  {
    printf("La cola ya existe.\n");
  }

  // Si se desea eliminar la cola para tareas de mantenimiento, puede utilizarse
  // esta función.
  // if (msgctl(id_cola, IPC_RMID, NULL) != -1)
  // {
  //   printf("Cola con ID %i eliminada correctamente.\n", id_cola);
  //   return -1;
  // }

  // Leemos el ID único para este usuario.
  printf("Ingresa un número ID único: ");
  scanf("%li", &mensaje_a_enviar.message_type);

  // Creamos el hilo de escucha.
  pthread_create(&hilo_escucha, NULL, imprimir_mensajes, (void *)mensaje_a_enviar.message_type);

  // Mostramos información antes de iniciar a leer mensajes.
  printf("Ahora puedes comenzar a escribir...\n");
  printf("Máximo %i caracteres, escribe \"%s\" para salir:\n\n", TAM_BUFFER_MENSAJES - 4, MENU_SALIR);

  // Ciclo principal para enviar mensajes.
  do
  {
    // Leemos el mensaje a enviar.
    fgets(mensaje_a_enviar.buffer, TAM_BUFFER_MENSAJES - 4, stdin);

    // Eliminamos el salto de línea (si existe.)
    int longitud = strlen(mensaje_a_enviar.buffer);
    if (mensaje_a_enviar.buffer[longitud - 1] == '\n')
    {
      mensaje_a_enviar.buffer[longitud - 1] = '\0';
    }

    // Verificamos que no sea la opción de salir.
    if (strcmp(mensaje_a_enviar.buffer, MENU_SALIR) != 0)
    {
      // Enviamos el mensaje.
      msgsnd(id_cola, &mensaje_a_enviar, sizeof(mensaje_a_enviar.buffer), 0);
    }
  } while (strcmp(mensaje_a_enviar.buffer, MENU_SALIR) != 0);

  // Finalizamos el hilo de escucha.
  pthread_cancel(hilo_escucha);

  // Mensaje final.
  printf("Programa finalizado correctamente.\n");

  // Exit status = 0.
  return 0;
}

/**
 * Imprimir Mensajes
 * Función que imprime los mensajes que se encuentren en la cola conforme se van recibiendo.
 * @param parametro_nombre El parámetro con el nombre en formato (void*)
 * @return void
 */
void *imprimir_mensajes(void *parametro_nombre)
{
  // Variables locales.
  // char *nombre = (char *)parametro_nombre;
  int tipo_mensaje = (int)parametro_nombre;
  key_t llave_cola;
  int id_cola;
  mensaje mensaje_recibido;

  // Obtenemos la llave.
  llave_cola = ftok(NOMBRE_LLAVE, ID_PROYECTO);

  // Obtenemos el ID de la cola.
  id_cola = msgget(llave_cola, 0);

  // Hilo infinito principal.
  while (1)
  {
    // Leemos el mensaje entrante.
    msgrcv(id_cola, &mensaje_recibido, sizeof(mensaje_recibido.buffer), 0, 0);

    // Si el mensaje no es nuestro, lo imprimimos, en otro caso, reenviamos.
    if (mensaje_recibido.message_type != tipo_mensaje)
    {
      // Mostramos el mensaje que llega.
      printf("\n[#%li]: %s\n", mensaje_recibido.message_type, mensaje_recibido.buffer);
    }
    else
    {
      // Reenviamos el mensaje que enviamos previamente ya que nosotros lo capturamos.
      msgsnd(id_cola, &mensaje_recibido, sizeof(mensaje_recibido.buffer), 0);
    }
  }
}