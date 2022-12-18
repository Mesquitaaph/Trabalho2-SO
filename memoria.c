#include "memoria.h"

// Array de frames que indica qual processo esta usando tal frame
// frames[i] = x significa que o processo x esta usando o frame i
// frames[i] = -1 significa que  o frame i esta livre
unsigned int frames[NUM_FRAMES];

/**
 * Inicia o array de frames com o valor `-1`, que representa um frame vazio.
*/
void iniciar_memoria() {
    memset(frames, -1, sizeof(unsigned int[NUM_FRAMES]));
}

/**
 * Realiza um acesso a `pagina` do processo `proc`.
*/
void acessar_pagina(Processo *proc, unsigned int pagina) {
    printf("P%d acessando pagina %d (t=%d)\n", proc->pid, pagina, getTempo());
    if (proc->tabela_paginas[pagina] == -1) {
        alocar_pagina(proc, pagina);
    } else {
        print_acesso_memoria_sem_alteracao(proc, pagina);
    }
    proc->momento_acessos[pagina] = getTempo();
    proc->prox_acesso += TEMPO_ACESSO_MEM;
}

/**
 * Aloca a `pagina` do processo `proc` em um frame vazio, realizando swap-out
 * se necessario
*/
void alocar_pagina(Processo *proc, unsigned int pagina) {
    if (proc->working_set == WSL) {
        substituir_pag_tabela(proc, pagina);
        return;
    }
    unsigned int f;
    for (f = 0u; f < NUM_FRAMES; f++) {
        if (frames[f] == -1) {
            frames[f] = proc->pid;
            adicionar_pag_tabela(proc, pagina, f);
            return;
        }
    }
    f = swap_out();
    frames[f] = proc->pid;
    adicionar_pag_tabela(proc, pagina, f);
}

/**
 * Realiza o swap-out do processo que esta ha mais tempo na memoria e retorna um
 * frame que foi liberado pelo swap-out
*/
unsigned int swap_out() {
    Fila *fila = getFila();
    Processo *mais_antigo = fila->atual->processo;
    for(Proc_Fila *pf = fila->atual->prox; pf != fila->atual; pf = pf->prox) {
        if(pf->processo->chegada_mem < mais_antigo->chegada_mem) {
            mais_antigo = pf->processo;
        }
    }

    memset(mais_antigo->tabela_paginas, -1, sizeof(unsigned int[PAGS_PROC]));
    memset(mais_antigo->momento_acessos, -1, sizeof(unsigned int[PAGS_PROC]));
    mais_antigo->chegada_mem = -1;
    mais_antigo->working_set = 0u;

    unsigned int frame_liberado = -1;
    for (unsigned int f = NUM_FRAMES-1; f < NUM_FRAMES; f--) {
        if (frames[f] == mais_antigo->pid) {
            frames[f] = -1;
            frame_liberado = f;
        }
    }
    printf("P%d sofreu swap out\n", mais_antigo->pid);
    printf("Frame %d liberado\n", frame_liberado);
    return frame_liberado;
}
