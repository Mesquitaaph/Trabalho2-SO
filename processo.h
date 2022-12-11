#ifndef PROCESSO_H_
#define PROCESSO_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "configs.h"

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

#endif