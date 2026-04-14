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

srand(seed);

    int *sequence = calloc(n, sizeof(int));

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
    printf("\nInitial sequence:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", sequence[i]);
    printf("\n");

    // calcula valor inicial
    double initial_losses = sequence_power_losses(sequence);
    printf("\nInitial losses: %lf\n", initial_losses);

    // pergunta se quer contar estados visitados
    int contar;
    printf("\nDeseja contar estados visitados? (1 = sim, 0 = nao): ");
    scanf("%d", &contar);
    ps_set_count_visits(contar);

// roda Simulated Annealing
simulated_annealing_power(sequence, n,
                         temp_inicial,   // temperatura inicial
                          temp_final,    // temperatura final
                          alpha);    // alpha

    double final_losses = sequence_power_losses(sequence);
    printf("Final losses SA: %lf\n", final_losses);

    // exibe resultado da contagem se estiver ativa
    if (contar)
    {
        int visited = ps_count_visited_states();
        printf("Estados distintos visitados: %d de %d possiveis\n",
               visited, (int)pow(2, n));
    }

    free(sequence);
    power_system_free();
    return 0;
}