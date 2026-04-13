#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sa_power.h"
#include "power_system_functions.h"

static int unif(int a, int b)
{
    return a + rand() % (b - a + 1);
}

static double rando(void)
{
    return (double)rand() / ((double)RAND_MAX + 1.0);
}

static void swap(int *sequence, int i, int j)
{
    int temp    = sequence[i];
    sequence[i] = sequence[j];
    sequence[j] = temp;
}

void simulated_annealing_power(int *sequence, int n,
                               double initial_temp,
                               double final_temp,
                               double alpha)
{
    double current_cost = sequence_power_losses(sequence);
    double best_cost    = current_cost;

    int *best_sequence = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        best_sequence[i] = sequence[i];

    double T = initial_temp;

    while (T > final_temp)
    {
        int i = unif(0, n - 1);
        int j;
        do {
            j = unif(0, n - 1);
        } while (j == i);

        swap(sequence, i, j);

        double new_cost = sequence_power_losses(sequence);
        double delta    = new_cost - current_cost;

        if (delta < 0 || exp(-delta / T) > rando())
        {
            current_cost = new_cost;

            if (current_cost < best_cost)
            {
                best_cost = current_cost;
                for (int k = 0; k < n; k++)
                    best_sequence[k] = sequence[k];
            }
        }
        else
        {
            swap(sequence, i, j);
        }

        T *= alpha;
    }

    for (int i = 0; i < n; i++)
        sequence[i] = best_sequence[i];

    printf("\nMelhor valor final: %lf\n", best_cost);

    free(best_sequence);
}