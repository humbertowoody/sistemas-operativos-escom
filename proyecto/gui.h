#ifndef GUI_H_INCLUIDO
#define GUI_H_INCLUIDO

// Constantes de operación
#define INICIALIZAR_PANTALLA_EXITO 1
#define INICIALIZAR_PANTALLA_ERROR -1
#define FINALIZAR_PANTALLA_EXITO 1
#define FINALIZAR_PANTALLA_ERROR -1

// Prototipos de funciones.
int inicializar_pantalla();
int finalizar_pantalla();
int obtener_filas_pantalla();
int obtener_columnas_pantalla();

#endif // GUI_H_INCLUIDO
