all: simulador

simulador: simulador.c configs.h globais.c globais.h processo.c processo.h fila.c fila.h memoria.c memoria.h
	gcc simulador.c globais.c fila.c processo.c memoria.c -o simulador 

run: simulador
	./simulador