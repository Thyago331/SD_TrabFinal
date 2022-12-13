// ****************************************************************
// *****         SISTEMAS DISTRIBUIDOS - TRABALHO MPI         *****
// ****************************************************************
//*                   Aproximação de PI (Wallis)                  *

//* NOME: Alfredo Savi | R.A: 1882872

#include <stdio.h>
#include <mpi.h>

#define NUM_ITER 300000000

long double pi_term(int n)
{
  return (2 * (long double)n / (2 * (long double)n - 1)) * (2 * (long double)n / (2 * (long double)n + 1));
}

int main()
{
  long double pi = 1, series_term = 1;

  double begin = MPI_Wtime();
  for (int i = 1; i <= NUM_ITER; i++)
  {
    series_term = pi_term(i);
    pi *= series_term;
  }
  pi *= 2;

  double end = MPI_Wtime();
  double time_spent = (double)(end - begin);
  printf("Pi: %.20Lf \t\t Tempo: %.10lf \n", pi, time_spent);

  return 0;
}