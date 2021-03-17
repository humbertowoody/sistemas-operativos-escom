# Prácticas

En este directorio se encuentran todos los códigos y elementos que se realizaron para cada una de las prácticas. A su vez, se incluyen instrucciones para ejecutar los distintos códigos que se pueden encontrar en las prácticas así como algunas metodologías comunes para diagnosticar algún error y solucionarlo.

Las carpetas de las prácticas **no incluyen el reporte** de la práctica, primeramente por respeto al profesor y segundo porque realmente no tiene tanto caso almacenarlo en git.

## ¿Cómo compilar y ejecutar?

Todos los códigos escritos aquí pueden encontrarse en dos variantes: `bash` y `C`.

### Códigos en Bash

El código en `bash` corresponde a los archivos con terminación `.sh`, y para ejecutarlos bastará con ejecutar:

```sh
$ ./Archivo.sh
```

Con lo que se ejecutarán las instrucciones contenidas en `Archivo.sh`. En caso de que el archivo no se pudiera ejecutar, será necesario verificar que el archivo cuente con el permiso de ejecución (en Linux y macOS) utilizando el comando `ls` de la siguiente forma:

```sh
$ ls -la .
total 0
drwxr-xr-x  4 humbertowoody  staff  128 Mar 16 18:22 .
drwxr-xr-x  8 humbertowoody  staff  256 Mar 15 12:58 ..
-rwxr-xr-x  1 humbertowoody  staff    0 Mar 16 18:22 ArchivoConPermisoDeEjecucion.sh
-rw-r--r--  1 humbertowoody  staff    0 Mar 16 18:21 ArchivoSinPermisoDeEjecucion.sh # ¡ojo aquí!
```

Así, se puede ver claramente que `ArchivoSinPermisoDeEjecucion.sh` **no cuenta** con permiso de ejecución por lo que nos arrojará el error:


```txt
bash: permission denied: ./ArchivoSinPermisoDeEjecucion.sh
```

Esto pues no cualquier *script* en bash puede ser ejecutado por defecto. Para añadir el permiso de ejecución, basta con usar el comando `chmod` de la siguiente forma:

```sh
$ chmod +x ArchivoSinPermisoDeEjecucion.sh
```

Y podremos verificar nuestro cambio mediante `ls` de la siguiente forma:

```sh
$ ls -la
total 0
drwxr-xr-x  4 humbertowoody  staff  128 Mar 16 18:22 .
drwxr-xr-x  8 humbertowoody  staff  256 Mar 15 12:58 ..
-rwxr-xr-x  1 humbertowoody  staff    0 Mar 16 18:22 ArchivoConPermisoDeEjecucion.sh
-rwxr-xr-x  1 humbertowoody  staff    0 Mar 16 18:22 ArchivoSinPermisoDeEjecucion.sh # ¡ojo aquí!
```

### Códigos en C

Todo el código que se realice en lenguaje C estará acorde al estándar C98, por lo que podremos utilizar *casi* cualquier compilador que conozcamos sin diferencias muy marcadas.

Para compilar desde la línea de comandos, utilizando `gcc` (puede usarse por igual `gcc`, `g++`, `clang` entre otros más), se emplea el siguiente comando:

```sh
$ gcc Archivo.c -o Ejecutable.out
```

> Nota: La extensión `*.out` es **completamente opcional**, en sistemas Linux y basados en UNIX (como macOS), la extensión `.out` es el estándar, pero en Windows puede sustituírse por `.exe` o a bien del programador.

Una vez realizada la compilación, se puede ejecutar nuestro binario de la siguiente forma:

```sh
$ ./Ejecutable.out
```

