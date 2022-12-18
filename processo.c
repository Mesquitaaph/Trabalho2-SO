#include "processo.h"
#include "globais.h"

unsigned int prox_pid = 1u;

Processo *criar_processo() {
    Processo *out = malloc(sizeof(Processo));
    out->pid = prox_pid++;
    out->working_set = 0u;
    out->chegada_mem = getTempo();
    out->prox_acesso = getTempo();
    memset(out->tabela_paginas, -1, sizeof(unsigned int[PAGS_PROC]));
    memset(out->momento_acessos, -1, sizeof(unsigned int[PAGS_PROC]));

    return out;
}

unsigned int pag_mais_antiga(Processo *proc) {
    unsigned int ultima_pag = -1;
    for (unsigned int p = 0; p < PAGS_PROC; p++) {
        if (proc->tabela_paginas[p] != -1 && 
            (ultima_pag == -1 || proc->momento_acessos[p] < proc->momento_acessos[ultima_pag])) {
            ultima_pag = p;
        }
    }
    return ultima_pag;
}

void adicionar_pag_tabela(Processo *proc, unsigned int pagina, unsigned int frame) {
    print_adicao_tabela_pagina(proc, pagina, frame);

    if (proc->working_set == 0) proc->chegada_mem = getTempo();
    
    proc->tabela_paginas[pagina] = frame;
    proc->working_set++;
}

void substituir_pag_tabela(Processo *proc, unsigned int pagina) {
        unsigned int ultima_pag = pag_mais_antiga(proc);

        print_substituicao_tabela_pagina(proc, pagina, ultima_pag);

        proc->tabela_paginas[pagina] = proc->tabela_paginas[ultima_pag];
        proc->tabela_paginas[ultima_pag] = -1;
        proc->momento_acessos[ultima_pag] = -1;
}

void print_adicao_tabela_pagina(Processo *proc, unsigned int pagina, unsigned int frame) {
    printf("Tabela de paginas do P%d:\n", proc->pid);
    for (unsigned int p=0; p < PAGS_PROC; p++) {
        printf("%d\t", p);
    }
    printf("\n");
    for (unsigned int p=0; p < PAGS_PROC; p++) {
        if (p == pagina) printf("-1->%d\t", frame);
        else printf("%d\t", proc->tabela_paginas[p]);
    }
    printf("\n\n");
}

void print_substituicao_tabela_pagina(Processo *proc, unsigned int pagina, unsigned int ultima_pag) {
    printf("Tabela de paginas do P%d:\n", proc->pid);
    for (unsigned int p=0; p < PAGS_PROC; p++) {
        printf("%d\t", p);
    }
    printf("\n");
    for (unsigned int p=0; p < PAGS_PROC; p++) {
        if (p == ultima_pag) printf("%d->-1\t", proc->tabela_paginas[p]);
        else if (p == pagina) printf("-1->%d\t", proc->tabela_paginas[ultima_pag]);
        else printf("%d\t", proc->tabela_paginas[p]);
    }
    printf("\n\n");
}

void print_acesso_memoria_sem_alteracao(Processo *proc, unsigned int pagina) {
    printf("Pagina %d ja estava na memoria.\n", pagina);
    printf("Tabela de paginas do P%d:\n", proc->pid);
    for (unsigned int p=0; p < PAGS_PROC; p++) {
        printf("%d\t", p);
    }
    printf("\n");
    for (unsigned int p=0; p < PAGS_PROC; p++) {
        printf("%d\t", proc->tabela_paginas[p]);
    }
    printf("\n\n");
}
