/**
 * libro.h
 * 
 * Este archivo contiene la definición de funciones y estructuras necesarias para las operaciones relacionadas con
 * libros en E-Shelf.
 */
#ifndef LIBRO_H_INCLUIDO
#define LIBRO_H_INCLUIDO

// Constantes de operación.
#define LONGITUD_MAXIMA_TITULO_LIBRO 255
#define LONGITUD_MAXIMA_DESCRIPCION_LIBRO 255
#define LONGITUD_MAXIMA_AUTOR_LIBRO 255
#define LONGITUD_MAXIMA_EDITORIAL_LIBRO 255
#define LONGITUD_MAXIMA_ISBN_LIBRO 13

/**
 * Estructura libro
 * - ISBN
 * - Título
 * - Descripción
 * - Autor
 * - Editorial
 * - Idioma del libro (en formato ISO-639-2 https://en.wikipedia.org/wiki/List_of_ISO_639-2_codes)
 * - Año de publicación
 * - Precio
 */
typedef struct estructura_libro
{
  char isbn[LONGITUD_MAXIMA_ISBN_LIBRO];
  char titulo[LONGITUD_MAXIMA_TITULO_LIBRO];
  char descripcion[LONGITUD_MAXIMA_DESCRIPCION_LIBRO];
  char autor[LONGITUD_MAXIMA_AUTOR_LIBRO];
  char editorial[LONGITUD_MAXIMA_EDITORIAL_LIBRO];
  char idioma_iso[3];
  int anio;
  float precio;
} libro;

// Prototipos de funciones.
int agregar_libro(libro);
int eliminar_libro_por_isbn(char *);
libro editar_libro(libro);
libro buscar_libro_por_isbn(char *);
libro buscar_libro_por_autor(char *);
libro buscar_libro_por_editorial(char *);

#endif // LIBRO_H_INCLUIDO
