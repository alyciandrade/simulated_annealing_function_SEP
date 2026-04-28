#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <libeps.h>
#include <time.h>
#include "sa_power.h"
#include "power_system_functions.h"

struct power_system_data *data = NULL;

int main(int argc, char *argv[])
{
    int n = power_system_init(ARQ_IEEE_30_BUS, &data);
    double temp_inicial = atof(argv[1]);
    double temp_final = atof(argv[2]);
    double alpha = atof(argv[3]);
    int seed = atoi(argv[4]); 
    int iteracoes_por_temp = atoi(argv[5]);
    int contar = atoi(argv[6]); 
    int operador = atoi(argv[7]);
    int *sequence = calloc(n, sizeof(int));

    srand(seed);


    // sequência inicial identidade
    for (int i = 0; i < n; i++)
        sequence[i] = i;

    // embaralhar sequência 
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = sequence[i];
        sequence[i] = sequence[j];
        sequence[j] = temp;
    }

    // mostra sequência embaralhada
    /*printf("\nInitial sequence:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", sequence[i]);
    printf("\n");*/

    // calcula valor inicial
    /*double initial_losses = sequence_power_losses(sequence);
    printf("\nInitial losses: %lf\n", initial_losses);*/

    // pergunta se quer contar estados visitados
    ps_set_count_visits(contar);

    int total_iteracoes;

    struct timespec inicio, fim;

    clock_gettime(CLOCK_MONOTONIC, &inicio);

    // roda Simulated Annealing
    total_iteracoes = simulated_annealing_power(sequence, n,
                            temp_inicial,   // temperatura inicial
                            temp_final,    // temperatura final
                            alpha,         // alpha
                            iteracoes_por_temp, //iterações 
                            operador);   //swap ou insert

    //mede o tempo de execução do SA
    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempo_execucao = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    //printf("Tempo de execucao SA: %lf segundos\n", tempo_execucao);
    //printf("Total de iteracoes: %d\n", total_iteracoes);

    int visited = 0;

    // exibe resultado da contagem se estiver ativa
    if (contar)
    {
        visited = ps_count_visited_states();
        //printf("Estados distintos visitados: %d de %d possiveis\n",
               //visited, (int)pow(2, n));
    }


    double final_losses = sequence_power_losses(sequence);
    //printf("Final losses SA: %lf\n", final_losses);

    printf("\n");
    printf("seed; temp_inicial; temp_final; alpha; iteracoes_por_temp; operador; final_losses; visited; total_iteracoes; tempo_execucao\n");
    printf("%d; %lf; %lf; %lf; %d; %d; %lf; %d; %d; %lf\n",
        seed, temp_inicial, temp_final, alpha, iteracoes_por_temp, operador, final_losses, visited, total_iteracoes, tempo_execucao);

    free(sequence);
    power_system_free();
    return 0;
}