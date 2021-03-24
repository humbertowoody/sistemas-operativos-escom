/**
 * Realizar un programa que cree tres hilos. El primer hilo se encargará de contabilizar las
 * ocurrencias de una cadena dentro de un archivo especifico y devolver el resultado al programa principal; el
 * segundo hilo copiará los archivos de su directorio actual a un subdirectorio que usted elija devolviendo al
 * programa principal el número de archivos copiados; el tercer hilo generará un archivo donde se reportarán
 * los resultados devueltos por los otros dos hilos.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <dirent.h>

// Constantes de operación.
#define NOM_ARCHIVO_RESULTADOS "resultados.txt"
#define TAM_MAX_NOM_ARCHIVO 256
#define TAM_MAX_NOM_DIRECTORIO 256
#define TAM_MAX_FRASE 64

// Estructura para los parámetros empleados durante la creación del hilo para contabilizar ocurrencias.
typedef struct parametros_contabilizar_ocurrencias
{
  char nombre_archivo[TAM_MAX_NOM_ARCHIVO];
  char frase[TAM_MAX_FRASE];
} parametros_contabilizar_ocurrencias;

// Estructura para los parámetros empleados durante la creación del hilo para copiar archivos.
typedef struct parametros_copiar_archivos
{
  char nombre_directorio[TAM_MAX_NOM_DIRECTORIO];
} parametros_copiar_archivos;

// Estructura para guardar los resultados de la ejecución de los primeros dos hilos.
typedef struct resultados_ejecucion
{
  int numero_ocurrencias;
  parametros_contabilizar_ocurrencias *parametros_cont_oc;
  int numero_archivos_copiados;
  parametros_copiar_archivos *parametros_copiar_ar;
} resultados_ejecucion;

// Prototipos de funciones
int contabilizar_ocurrencias(char *, char *);          // Función que contabiliza las ocurrencias de una frase en un archivo.
int copiar_archivos_en_directorio(char *);             // Función que copia archivos al directorio destino.
int copiar_archivo(char *, char *);                    // Función que copia un archivo
void *func_hilo_contabilizar_ocurrencias(void *);      // Función que se ejecuta dentro de un hilo para contabilizar las ocurrencias de una frase en un archivo.
void *func_hilo_copiar_archivos_en_directorio(void *); // Función que se ejecuta dentro de un hilo y copia los archivos del directorio actual al especificado.
void *func_hilo_generar_reporte_resultados(void *);    // Función que se ejecuta dentro de un hilo y genera un reporte de resultados de operación.

// Función principal.
int main(int argc, char *argv[])
{
  // Variables locales.
  parametros_contabilizar_ocurrencias *parametros_cont_oc = (parametros_contabilizar_ocurrencias *)malloc(sizeof(parametros_contabilizar_ocurrencias));
  parametros_copiar_archivos *parametros_copiar_ar = (parametros_copiar_archivos *)malloc(sizeof(parametros_copiar_archivos));
  resultados_ejecucion *resultados = (resultados_ejecucion *)malloc(sizeof(resultados_ejecucion));
  pthread_t hilo_contabilizar_ocurrencias,
      hilo_copiar_archivos,
      hilo_generar_reporte_resultados;
  void *retorno_hilo_contabilizar_ocurrencias;
  void *retorno_hilo_copiar_archivos;

  // Leemos del usuario el nombre del archivo para contabilizar las ocurrencias.
  printf("Introduzca el nombre del archivo para buscar ocurrencias: ");
  scanf("%s", parametros_cont_oc->nombre_archivo);

  // Leemos la frase a buscar en el archivo.
  printf("Introduzca la frase a buscar en el archivo: ");
  scanf("%s", parametros_cont_oc->frase);

  // Confirmación para el usuario.
  printf("Se contabilizarán las ocurrencias de \"%s\" en el archivo: %s\n", parametros_cont_oc->frase, parametros_cont_oc->nombre_archivo);

  // Leemos el directorio destino para la operación de copia de archivos.
  printf("Introduzca la ruta (relativa o absoluta) del directorio destino de la copia de los archivos en este directorio\n");
  printf("la ruta no debe contener la barra inclinada frontal final (/):\n> ");
  scanf("%s", parametros_copiar_ar->nombre_directorio);

  // Confirmación para el usuario.
  printf("Se copiarán todos los archivos en el directorio de ejecución del presente programa al directorio: %s\n", parametros_copiar_ar->nombre_directorio);

  // Creamos el hilo para contar ocurrencias.
  pthread_create(&hilo_contabilizar_ocurrencias, NULL, func_hilo_contabilizar_ocurrencias, (void *)parametros_cont_oc);

  // Creamos el hilo para copiar archivos.
  pthread_create(&hilo_copiar_archivos, NULL, func_hilo_copiar_archivos_en_directorio, (void *)parametros_copiar_ar);

  // Esperamos que finalicen ambos hilos.
  pthread_join(hilo_contabilizar_ocurrencias, &retorno_hilo_contabilizar_ocurrencias);
  pthread_join(hilo_copiar_archivos, &retorno_hilo_copiar_archivos);

  // Asignamos los parámetros para los resultados.
  resultados->numero_ocurrencias = (int)retorno_hilo_contabilizar_ocurrencias;
  resultados->parametros_cont_oc = parametros_cont_oc;
  resultados->numero_archivos_copiados = (int)retorno_hilo_copiar_archivos;
  resultados->parametros_copiar_ar = parametros_copiar_ar;

  // Verificamos el valor de retorno de la operación de contabilización de ocurrencias.
  if (resultados->numero_ocurrencias != -1)
  {
    // Si no ocurrió un error, mostramos una confirmación del resultado.
    printf("Se encontraron %i ocurrencias de \"%s\" en: %s\n", (int)retorno_hilo_contabilizar_ocurrencias, parametros_cont_oc->frase, parametros_cont_oc->nombre_archivo);
  }
  else
  {
    // Si hubo un error, mostramos este mensaje y salimos.
    printf("Ocurrió un error al tratar de contabilizar las ocurrencias de la frase en el archivo.\n");
    return -1;
  }

  // Verificamos el valor de retorno de la operación de copiado de archivos.
  if (resultados->numero_archivos_copiados != -1)
  {
    // Si no ocurrió un error, mostramos una confirmación del resultado.
    printf("Se copiaron %i archivos al directorio: %s\n", resultados->numero_archivos_copiados, parametros_copiar_ar->nombre_directorio);
  }
  else
  {
    // Si hubo un error, mostramos este mensaje y salimos.
    printf("Ocurrió un error al tratar de realizar la copia de archivos.\n");
    return -1;
  }

  // Creamos hilo para escribir resultados.
  pthread_create(&hilo_generar_reporte_resultados, NULL, func_hilo_generar_reporte_resultados, (void *)resultados);

  // Esperamos a que finalice hilo para crear resultados.
  pthread_join(hilo_generar_reporte_resultados, NULL);

  // Mensaje para el usuario.
  printf("El archivo \"%s\" contiene los resultados de la ejecución.\n", NOM_ARCHIVO_RESULTADOS);

  // Exit status = 0.
  return 0;
}

/**
 * Copiar Archivos
 * Función que copia todos los archivos presentes en el directorio actual de ejecución del programa
 * a un directorio destino especificado por el usuario.
 * @param nom_directorio_destino El directorio destino para los archivos copiados.
 * @return Un entero con el número de archivos copiados o -1 si ocurrió algún error.
 */
int copiar_archivos_en_directorio(char *nom_directorio_destino)
{
  // Variables locales.
  DIR *directorio_actual;
  struct dirent *directorio_actual_str;
  char nombre_nuevo_archivo_copia[TAM_MAX_NOM_ARCHIVO];
  int resultado_copia_archivo,
      cont_archivos_copiados = 0;

  // Abrimos el directorio actual.
  directorio_actual = opendir(".");

  // Verificamos que se haya podido abrir el directorio actual.
  if (directorio_actual)
  {
    // Iteramos sobre cada elemento dentro del directorio.
    while ((directorio_actual_str = readdir(directorio_actual)) != NULL)
    {
      // Verificamos que el elemento sea de tipo archivo.
      if (directorio_actual_str->d_type == DT_REG)
      {
        // Creamos el nombre del archivo copia
        sprintf(nombre_nuevo_archivo_copia, "%s/%s", nom_directorio_destino, directorio_actual_str->d_name);

        // Copiamos el archivo.
        resultado_copia_archivo = copiar_archivo(directorio_actual_str->d_name, nombre_nuevo_archivo_copia);

        // Verificamos que la copia haya sido exitosa.
        if (resultado_copia_archivo == 0)
        {
          // Aumentamos el contador.
          cont_archivos_copiados++;
        }
        else
        {
          printf("El archivo: \"%s\" no pudo ser copiado.\n", directorio_actual_str->d_name);
        }
      }
    }

    // Cerramos el directorio actual.
    closedir(directorio_actual);
  }
  else
  {
    // Si no se pudo abrir el directorio actual, regresamos -1.
    return -1;
  }

  // Regresamos el contador de archivos copiados.
  return cont_archivos_copiados;
}

/**
 * Copiar Archivo
 * Función que copia un archivo en otro.
 * @param nom_archivo_original El nombre del archivo a copiar
 * @param nom_archivo_destino El nombre del archivo destino
 * @return Un entero 0 si la ejecución fue correcta, otro valor en caso de error.
 */
int copiar_archivo(char *nom_archivo_original, char *nom_archivo_destino)
{
  // Variables locales.
  FILE *archivo_origen,
      *archivo_destino;
  char c;

  // Abrimos el archivo origen en modo lectura.
  archivo_origen = fopen(nom_archivo_original, "r");

  // Abrimos el archivo destino en modo escritura.
  archivo_destino = fopen(nom_archivo_destino, "w");

  // Verificamos si pudimos abrir ambos archivos.
  if (archivo_origen == NULL || archivo_destino == NULL)
  {
    // Regresamos un valor de error.
    return -1;
  }

  // Iteramos sobre los contenidos del archivo_origen.
  while ((c = fgetc(archivo_origen)) != EOF)
  {
    // Escribimos el dato en el archivo destino.
    fputc(c, archivo_destino);
  }

  // Cerramos ambos archivos.
  fclose(archivo_origen);
  fclose(archivo_destino);

  // En este punto la ejecución fue correcta, regresamos un cero.
  return 0;
}

/**
 * Función de Hilo: Copiar Archivos
 * Esta función contiene el ciclo de ejecución para el hilo que copia todos los archivos en el directorio
 * actual a un directorio destino.
 * @param parametros_originales Una estructura de tipo (void*) que se castea a parametros_copiar_archivos.
 * @return Un dato tipo (void*) que se castea a un entero con el resultado de la operación.
 */
void *func_hilo_copiar_archivos_en_directorio(void *parametros_originales)
{
  // Variables locales.
  parametros_copiar_archivos *parametros = (parametros_copiar_archivos *)parametros_originales;
  int resultado;

  // Llamamos a la función con la implementación del flujo.
  resultado = copiar_archivos_en_directorio(parametros->nombre_directorio);

  // Regresamos el resultado.
  return (void *)resultado;
}

/**
 * Contabilizar Ocurrencias
 * Función que contabiliza el número de ocurrencias de una frase dentro de un archivo
 * particular.
 * @param nombre_archivo Una cadena de caracteres con el nombre del archivo para contabilizar las ocurrencias
 * @param frase Una cadena de caracteres con la frase a buscar.
 * @return Un entero con el número de ocurrencias, -1 si ocurrió un error abriendo el archivo.
 */
int contabilizar_ocurrencias(char *nombre_archivo, char *frase)
{
  // Variables locales.
  FILE *archivo;              // El archivo para las operaciones.
  char buffer[512];           // Un búffer para almacenar 512 bytes de información.
  int numero_ocurrencias = 0; // Un contador del número de ocurrencias.

  // Abrimos el archivo con control de errores.
  if ((archivo = fopen(nombre_archivo, "r")) == NULL)
  {
    return -1;
  }

  // Leemos una línea del archivo mientras no encontremos el EOF.
  while (fgets(buffer, 512, archivo) != NULL)
  {
    // Verificamos si existe nuestra frase en la línea que obtuvimos.
    if ((strstr(buffer, frase)) != NULL)
    {
      // En caso de que si, aumentamos el contador.
      numero_ocurrencias++;
    }
  }

  // Cerramos el archivo si sigue abierto.
  if (archivo)
  {
    fclose(archivo);
  }

  // Regresamos el número de ocurrencias.
  return numero_ocurrencias;
}

/**
 * Función Hilo Contabilizar Ocurrencias
 * Esta función contiene el ciclo de ejecución para el hilo que contabiliza las ocurrencias de una frase
 * en un archivo.
 * @param parametros_originales Una estructura de tipo (void*) que se castea a parametros_contabilizar_ocurrencias.
 * @return Un dato tipo (void*) que se castea a un entero con el resultado de la operación.
 */
void *func_hilo_contabilizar_ocurrencias(void *parametros_originales)
{
  // Variables locales.
  parametros_contabilizar_ocurrencias *parametros = (parametros_contabilizar_ocurrencias *)parametros_originales;
  int resultado = 0;

  // Llamamos a la función.
  resultado = contabilizar_ocurrencias(parametros->nombre_archivo, parametros->frase);

  // Regresamos el resultado.
  return (void *)resultado;
}

/**
 * Función de Hilo: Generar Reoprte de Resultados
 * Esta función representa el flujo de trabajo para generar un reporte de
 * resultados en un archivo determinado.
 * @param parametros_funcion Una estructura de tipo (void*) que contiene resultados_ejecucion.
 * @return void
 */
void *func_hilo_generar_reporte_resultados(void *parametros_funcion)
{
  // Variables locales.
  resultados_ejecucion *resultados = (resultados_ejecucion *)parametros_funcion;
  FILE *archivo;

  // Abrimos el archivo en modo de escritura + actualización (si el archivo existe, se sobreescribe).
  archivo = fopen(NOM_ARCHIVO_RESULTADOS, "w+");

  // Escribimos los resultados al archivo.
  fprintf(archivo, "El número de ocurrencias de la frase \"%s\" en el archivo \"%s\" es: %i\n", resultados->parametros_cont_oc->frase, resultados->parametros_cont_oc->nombre_archivo, resultados->numero_ocurrencias);
  fprintf(archivo, "El número de archivos copiados al directorio \"%s\" es: %i\n", resultados->parametros_copiar_ar->nombre_directorio, resultados->numero_archivos_copiados);

  // Cerramos el archivo si sigue abierto.
  if (archivo)
  {
    fclose(archivo);
  }

  // Regresamos un valor cero.
  return 0;
}
