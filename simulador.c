#include <stdio.h>

#include "globais.h"
#include "fila.h"
#include "processo.h"
#include "memoria.h"

int main(int argc, char const *argv[])
{
    unsigned int prox_chegada_proc = 0u;
    unsigned int num_procs = 0u;
    setTempo(0u);
    iniciarFila();
    iniciar_memoria();
    Fila *fila = getFila();

    while(1) {
        if (num_procs < MAX_NUM_PROCS && 
            (num_procs == 0 || prox_chegada_proc <= fila->atual->prox->processo->prox_acesso)) {
            setTempo(prox_chegada_proc);
            Processo *novo_proc = criar_processo();
            adicionar_proc(fila, novo_proc);
            printf("O proceso P%d foi criado.\n", novo_proc->pid);
            num_procs++;
            prox_chegada_proc += TEMPO_CRIA_PROC;
        }

        andar_fila(fila);
        setTempo(fila->atual->processo->prox_acesso);
        acessar_pagina(fila->atual->processo, rand() % PAGS_PROC);
    }
    
    return 0;
}
