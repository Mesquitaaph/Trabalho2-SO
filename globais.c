#include "globais.h"

// Instante de tempo em que o simulador esta
unsigned int t;

// Fila circular dos processos. Organiza os acessos a memoria
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