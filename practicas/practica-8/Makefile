# Makefile para compilar y ejecutar rápidamente el código de la práctica.

# ¿Cómo utilizar?
# `make` - Realiza la compilación
# `make clean` - Elimina el ejecutable
# `make install`- Instala el ejecutable en /usr/local/bin
# `make uninstall` - Desinstala el ejecutable de /usr/local/bin

# El nombre del ejecutable
TARGET=Practica81.out 

# El directorio dónde se encuentra el código fuente
SRC=.

# Obtiene todos los archivos *.c en el directorio del código fuente
SRC_FILES=$(wildcard $(SRC)/*.c)

# Especificamos el compilador
CXX=gcc

# Banderas de compilación
CXXFLAGS=-Wall -Wextra -Wpedantic

# Librerías para compilación
CXXLIBS=-lncurses

# Construye el binario
$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) $(CXXLIBS) -o $(TARGET)

# Elimina el binario
clean:
	rm -f $(TARGET)

# Instala el binario en /usr/local/bin
install: $(TARGET)
	cp $(TARGET) /usr/local/bin

# Elimina el binario de /usr/local/bin
uninstall:
	rm -f /usr/lcoal/bin/$(TARGET)
