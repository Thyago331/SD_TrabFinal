// ****************************************************************
// *****         SISTEMAS DISTRIBUIDOS - TRABALHO MPI         *****
// ****************************************************************
//*                   Aproximação de PI (Wallis)                  *

//* NOME: Alfredo Savi | R.A: 1882872

#include <stdio.h>
#include <mpi.h>

#define NUM_ITER 500000000

long double pi_term(int n)
{
  return (2 * (long double)n / (2 * (long double)n - 1)) * (2 * (long double)n / (2 * (long double)n + 1));
}

int main(int argc, char **argv)
{
  double begin = MPI_Wtime();
  long double pi = 1, pi_partial = 1, series_term = 1;
  int size, rank;
  long start, end;

  MPI_Status status;
  MPI_Init(&argc, &argv);               // daqui pra baixo, ocorre o paralelismo e acaba no MPI_Finalize
  MPI_Comm_size(MPI_COMM_WORLD, &size); // size é o numero de threads q vc passou como argumento
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); // rank é o numero da thread q vc está

  start = NUM_ITER * rank / size + 1; // aqui ta dividndo um intervalo para todas as threads, exemplo: 50 iterações, utilizando 2 threads fica 25 pra cada (ta fazendo isso)
  end = NUM_ITER * (rank + 1) / size;

  for (long i = start; i <= end; i++)
  {
    series_term = pi_term(i);
    pi *= series_term;
  }

  printf("Process %d: start = %10ld, end = %ld | pi_partial = %Lf\n", rank, start, end, pi);

  if (rank != 0)
    MPI_Send(&pi, 1, MPI_LONG_DOUBLE, 0, 1, MPI_COMM_WORLD);
  else
  { // juntando cada pedaço paralelisado para dar o resultado final
    for (long j = 1; j < size; j++)
    {
      MPI_Recv(&pi_partial, 1, MPI_LONG_DOUBLE, j, 1, MPI_COMM_WORLD, &status);
      pi *= pi_partial;
    }
    pi *= 2;
  }

  if (rank == 0)
  {
    double end = MPI_Wtime();
    double time_spent = (double)(end - begin);
    printf("Pi: %.20Lf \t\t Tempo: %.10lf \n", pi, time_spent);
  }

  MPI_Finalize();
  return 0;
}