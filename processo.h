#ifndef PROCESSO_H_
#define PROCESSO_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "configs.h"

/**
 * Estrutura que representa um processo
*/
typedef struct Processo {
    unsigned int pid;
    unsigned int tabela_paginas[PAGS_PROC];
    unsigned int momento_acessos[PAGS_PROC];
    unsigned int working_set;
    unsigned int chegada_mem;
    unsigned int prox_acesso;
} Processo;

Processo *criar_processo();
unsigned int pag_mais_antiga(Processo *proc);
void adicionar_pag_tabela(Processo *proc, unsigned int pagina, unsigned int frame);
void substituir_pag_tabela(Processo *proc, unsigned int pagina);
void print_adicao_tabela_pagina(Processo *proc, unsigned int pagina, unsigned int frame);
void print_substituicao_tabela_pagina(Processo *proc, unsigned int pagina, unsigned int ultima_pag);
void print_acesso_memoria_sem_alteracao(Processo *proc, unsigned int pagina) ;
#endif
