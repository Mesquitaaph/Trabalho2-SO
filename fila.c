#include "fila.h"

Fila *criar_fila() {
    Fila *out = malloc(sizeof(Fila));
    out->atual = NULL;

    return out;
}

void adicionar_proc(Fila *fila, Processo *proc) {
    if (fila->atual == NULL) {
        fila->atual = malloc(sizeof(Proc_Fila));
        fila->atual->processo = proc;
        fila->atual->prox = fila->atual;
        return;
    }

    Proc_Fila *temp = fila->atual->prox;
    fila->atual->prox = malloc(sizeof(Proc_Fila));
    fila->atual->prox->processo = proc;
    fila->atual->prox->prox = temp;
}

void andar_fila(Fila *fila) {
    if (fila->atual == NULL) return;
    fila->atual = fila->atual->prox;
}