//
// Created by rafael on 03/02/26.
//

#ifndef POWER_SYSTEM_FUNCTIONS_H
#define POWER_SYSTEM_FUNCTIONS_H

struct power_system_data;

int    power_system_init(char *filename, struct power_system_data **data);
void   power_system_free(void);
double sequence_power_losses(int *sequence);


void ps_set_count_visits(int count_visits); //Ativa ou desativa a contagem de visitas aos estados.

/* Varre o vetor de contagem e retorna quantos estados distintos foram visitados.
 Retorna -1 se a contagem estiver desativada.*/
int ps_count_visited_states(void); 

#endif 