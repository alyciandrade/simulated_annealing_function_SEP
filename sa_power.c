#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

static void insert(int *sequence, int n, int i, int j)
{
    int elem = sequence[i];

    if (i < j)
        for (int k = i; k < j; k++)
            sequence[k] = sequence[k + 1];
    else
        for (int k = i; k > j; k--)
            sequence[k] = sequence[k - 1];

    sequence[j] = elem;
}

int simulated_annealing_power(int *sequence, int n,
                              double initial_temp,
                              double final_temp,
                              double alpha,
                              int iteracoes_por_temperatura)
{
    double current_cost = sequence_power_losses(sequence);
    double best_cost    = current_cost;

    int *best_sequence = malloc(n * sizeof(int));
    int *backup        = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        best_sequence[i] = sequence[i];

    double T = initial_temp;
    int iteration = 0;

    while (T > final_temp)
    {
        iteration++;

        int i = unif(0, n - 1);
        int j;
        do {
            j = unif(0, n - 1);
        } while (j == i);

        int operador = rand() % 2;
        double new_cost, delta;

        if (operador == 0)
        {
            // --- SWAP ---
            swap(sequence, i, j);
            new_cost = sequence_power_losses(sequence);
            delta    = new_cost - current_cost;

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
                swap(sequence, i, j);
        }
        else
        {
            // --- INSERT ---
            memcpy(backup, sequence, n * sizeof(int));
            insert(sequence, n, i, j);
            new_cost = sequence_power_losses(sequence);
            delta    = new_cost - current_cost;

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
                memcpy(sequence, backup, n * sizeof(int));
        }

        if (iteration % iteracoes_por_temperatura == 0)
            T *= alpha;
    }

    for (int i = 0; i < n; i++)
        sequence[i] = best_sequence[i];

    free(best_sequence);
    free(backup);

    return iteration;
}