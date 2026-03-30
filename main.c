#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <libeps.h>
#include <time.h>
#include "sa_power.h"
#include "power_system_functions.h"

struct power_system_data *data = NULL;

int main(void)
{
    int n = power_system_init(ARQ_IEEE_30_BUS, &data);

    srand(time(NULL));

int *sequence = calloc(n, sizeof(int));

// sequência inicial identidade
for (int i = 0; i < n; i++)
    sequence[i] = i;

// embaralhar sequência (Fisher-Yates)
for (int i = n - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    int temp = sequence[i];
    sequence[i] = sequence[j];
    sequence[j] = temp;
}

//mostra sequência embaralhada
printf("\nInitial sequence:\n");
for (int i = 0; i < n; i++)
    printf("%d ", sequence[i]);
printf("\n");

// calcula valor inicial
double initial_losses = sequence_power_losses(sequence);
printf("\nInitial losses: %lf\n", initial_losses);

// roda Simulated Annealing
simulated_annealing_power(sequence, n,
                         200.0,   // temperatura inicial
                          0.5,    // temperatura final
                          0.7);    // alpha

double final_losses = sequence_power_losses(sequence);
printf("Final losses SA: %lf\n", final_losses);

free(sequence);
    power_system_free();
    return 0;
}