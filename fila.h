#ifndef FILA_H_
#define FILA_H_

#include <stdlib.h>
#include "processo.h"

typedef struct Proc_Fila Proc_Fila;
struct Proc_Fila {
    Processo *processo;
    Proc_Fila *prox;

};

typedef struct Fila {
    Proc_Fila *atual;
} Fila;

Fila *criar_fila();
void adicionar_proc(Fila *fila, Processo *proc);
void andar_fila(Fila *fila);

#endif