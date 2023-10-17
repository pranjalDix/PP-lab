#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define n_threads 8

static long num_steps = 100000;
double steps;

void main()
{
    int i;
    steps = 1.0 / (double)num_steps;
    double x = 0, pie = 0;
    double sum[n_threads];

#pragma omp parallel private(i, x)
    {
        int id = omp_get_thread_num();
        for (i = id, sum[id] = 0.0; i < num_steps; i += n_threads)
        {
            x = (i + 0.5) * steps;
            sum[id] += 4.0 / (1.0 + x * x);
        }
    }

    for (int i = 1; i < n_threads; i++)
        sum[0] += sum[i];

    pie = sum[0] / num_steps;
    printf("pi = %6.12f\n", pie);
}