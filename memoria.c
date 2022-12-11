#include "memoria.h"

unsigned int frames[NUM_FRAMES];

void iniciar_memoria() {
    memset(frames, -1, sizeof(unsigned int[NUM_FRAMES]));
}

void acessar_pagina(Processo *proc, unsigned int pagina) {
    printf("P%d acessando pagina %d (t=%d)\n", proc->pid, pagina, getTempo());
    if (proc->tabela_paginas[pagina] == -1) {
        alocar_pagina(proc, pagina);
    } 
    proc->momento_acessos[pagina] = getTempo();
    proc->prox_acesso += TEMPO_ACESSO_MEM;
}

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
    printf("f=%d\n", frame_liberado);
    return frame_liberado;
}