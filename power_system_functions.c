//
// Created by rafael on 03/02/26.
//

#include <stdlib.h>
#include <math.h>
#include <libeps.h>
#include <assert.h>
#include "power_system_functions.h"

#include <stdio.h>

#define PENALTY_FACTOR 1E9

struct power_system_data
{
    eps *sep;
    param_fdpf param;
    int nAdjustments;
    adjustment *adjustments;
    double *fitness;
    // fazer o vetor de contagem
};

struct power_system_data *data_ps = NULL;

int power_system_init(char *filename, struct power_system_data **data)
{
    *data = (struct power_system_data*)calloc(1, sizeof(struct power_system_data));
    data_ps = *data;
    data_ps->sep = new_EPS(filename);

    init_fdpf_parameters(&(data_ps->param));
    data_ps->param.voltageControlPVBusType = 1;
    data_ps->param.tol = 1E-6;
    data_ps->param.printDetails = 0;
    data_ps->param.flatstart = 1;
    data_ps->param.xB = 1;
    data_ps->param.maximumNumberIterations = 20;

    data_ps->adjustments = optimal_reactive_adjustments(data_ps->sep, &(data_ps->nAdjustments));
    data_ps->fitness = (double *)calloc((int)(pow(2, data_ps->nAdjustments)), sizeof(double)); // copiar essa linha pq ele aloca o vetor de contagem

    assert(data_ps->fitness != NULL);

    return data_ps->nAdjustments;
}

void power_system_free(void)
{
    free_Adjustments(data_ps->adjustments);
    free_EPS(data_ps->sep);
    free(data_ps->fitness);
    free(data_ps);
    data_ps = NULL;
}

static void applyAdjustment(barra barras[], ligacao ligacoes[], adjustment a)
{
    if (a.tipo == 0)
    {
        barras[a.k].v = a.valor;
        barras[a.k].vEsp = barras[a.k].v;
    }
    else if (a.tipo == 1)
    {
        barras[a.k].bsh = a.valor;
    }
    else if (a.tipo == 2)
    {
        ligacao *lig;
        int aux = 0;
        if (ligacoes[a.k].prox->j < ligacoes[a.k].ant->j)
        {
            lig = ligacoes[a.k].prox;
            while (lig != NULL)
            {
                if (lig->j == a.m)
                {
                    if (aux == a.ordemtap)
                    {
                        lig->info->tap = a.valor;
                        break;
                    }
                    else
                    {
                        aux++;
                    }
                }

                lig = lig->prox;
            }
        }
        else
        {
            lig = ligacoes[a.k].ant;
            while (lig != NULL)
            {
                if (lig->j == a.m)
                {
                    if (aux == a.ordemtap)
                    {
                        lig->info->tap = a.valor;
                        break;
                    }
                    else
                    {
                        aux++;
                    }
                }

                lig = lig->ant;
            }
        }
    }
}

static int assess_operating_point_by_index_fdpf(eps *system, param_fdpf param_FD, unsigned long index, int nAdjusts, adjustment adjustments[])
{

    for (int k = 0; k < system->nB; k++)
    {

        system->barras[k].v = system->barras[k].v0;
        // barras[k].theta = barras[ref].theta;
        system->barras[k].vEsp = system->barras[k].v0;
        system->barras[k].bsh = system->barras[k].bsh0;
        ligacao *lig;
        lig = system->ligacoes[k].prox;
        while (lig != NULL)
        {
            lig->info->tap = lig->info->tap0;
            lig = lig->prox;
        }

        system->barras[k].flag = 0;
        if (system->barras[k].tipo == 4)
        {
            if (k == system->ref)
            {
                system->barras[k].tipo = 3;
                system->nPV = system->nPV - 1;
            }
            else
            {
                system->barras[k].tipo = 2;
                system->nPQ = system->nPQ - 1;
                system->nPV = system->nPV + 1;
            }
        }
        else if (system->barras[k].tipo == 5)
        {
            system->barras[k].tipo = 0;
            system->nPQ = system->nPQ + 1;
            system->nPV = system->nPV - 1;
        }
    }

    u_long new_ind;
    for (u_long i = 0; i < nAdjusts; ++i)
    {
        new_ind = index | ((unsigned long)(1) << i);
        if (new_ind == index)
        {
            applyAdjustment(system->barras, system->ligacoes, adjustments[i]);
        }
    }

    ret_fdpf retorno = fdpf(system, param_FD);
    return retorno.conv;

}

static double fitness_function(unsigned long n)
{
    assess_operating_point_by_index_fdpf(data_ps->sep, data_ps->param, n, data_ps->nAdjustments, data_ps->adjustments);
    double fit = losses(data_ps->sep);
    fit += power_flow_equations_penalty(data_ps->sep, data_ps->param.tol, 2, PENALTY_FACTOR);
    fit += voltage_magnitudes_limits_penalty(data_ps->sep, data_ps->param.tol, 2, PENALTY_FACTOR);
    fit += reactive_generations_limits_penalty(data_ps->sep, data_ps->param.tol, 2, PENALTY_FACTOR);
    return fit;
}

double sequence_power_losses(int *sequence)
{
    double power_losses = 0;
    unsigned long index = 0;
    if (data_ps->fitness[index] == 0)
    {
        data_ps->fitness[index] = fitness_function(index);
    }
    power_losses += data_ps->fitness[index];
    //printf("%lf/n", data_ps->fitness[index]);

    for (u_long i = 0; i < data_ps->nAdjustments; i++)
    {
        index = index | ((unsigned long)(1) << sequence[i]);

        if (data_ps->fitness[index] == 0)
        {
            data_ps->fitness[index] = fitness_function(index);
        }
        //printf("%lf/n", data_ps->fitness[index]);
        power_losses += data_ps->fitness[index];
    }
    return power_losses;
}
