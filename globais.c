#include "globais.h"

unsigned int t;
Fila *fila_procs;

unsigned int getTempo() {
    return t;
}

void setTempo(unsigned int novo_t) {
    t = novo_t;
}

Fila *getFila() {
    return fila_procs;
}

void iniciarFila() {
    fila_procs = criar_fila();
}