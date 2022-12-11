#ifndef MEMORIA_H_
#define MEMORIA_H_

#include <stdlib.h>

#include "configs.h"
#include "processo.h"
#include "fila.h"
#include "globais.h"

void iniciar_memoria();
void acessar_pagina(Processo *proc, unsigned int pagina);
void alocar_pagina(Processo *proc, unsigned int pagina);
unsigned int swap_out();

#endif