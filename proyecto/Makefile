# Makefile
# Con este archivo puedes utilizar el comando `make` para compilar, ejecutar
# y actualizar disintos módulos del proyecto de forma fácil y eficaz.
# Sistemas Operativos ESCOM 2021.

# Configuración del compilador
CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic

# Configuración del linker
LDFLAGS=-lncurses -lpthread

# Binario de Proceso de Control.
PROCESOCONTROL=e_shelf_control
PROCESOCONTROL_OBJS:= e_shelf_control.o control.o archivo.o hilo.o memoria_compartida.o

# Binario de Proceso Cliente.
CLIENTE=e_shelf_cliente
CLIENTE_OBJS:= e_shelf_cliente.o

# Binario de Proceso Proveedor.
PROVEEDOR=e_shelf_proveedor
PROVEEDOR_OBJS:=e_shelf_proveedor.o proveedor.o gui_proveedor.o

# Binario de Proceso de Seeding.
SEEDER=e_shelf_seeder
SEEDER_OBJS:=e_shelf_seeder.o archivo.o

# Generar todo
all: $(PROCESOCONTROL) $(CLIENTE) $(PROVEEDOR) $(SEEDER)

# Generar el Proceso de Control
$(PROCESOCONTROL): $(PROCESOCONTROL_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o$@ $^

# Generar el Proceso de Control
$(CLIENTE): $(CLIENTE_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o$@ $^

# Generar el Proceso de Control
$(PROVEEDOR): $(PROVEEDOR_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o$@ $^

$(SEEDER): $(SEEDER_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o$@ $^

# Compilar archivos objeto
%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o$@ $<

# Limpiar
clean:
	rm -f *.o
	rm -f $(PROCESOCONTROL) $(CLIENTE) $(PROVEEDOR) $(SEEDER)

# No sé.
.PHONY: all clean
