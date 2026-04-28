#ifndef SA_POWER_H
#define SA_POWER_H

int simulated_annealing_power(int *sequence, int n,
                              double initial_temp,
                              double final_temp,
                              double alpha,
                              int iteracoes_por_temperatura,
                              int operador);
                              
#endif