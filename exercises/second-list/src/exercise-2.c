/*
    Given the following piece of code, it is required to write a program in order to 
    support its execution.

    MPI_Comm_size(aux, &aux1);
    MPI_Comm_rank(aux, &aux2);
    MPI_Get_processor_name(aux3, &aux4);
    MPI_Get_version (&aux5, &aux6);

    This code implements this program.
*/ 

#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  MPI_Comm aux = MPI_COMM_WORLD;
  int aux1, aux2, aux4, aux5, aux6;
  char aux3[MPI_MAX_PROCESSOR_NAME];

  MPI_Init(&argc, &argv);
  MPI_Comm_size(aux, &aux1); 
  MPI_Comm_rank(aux, &aux2);
  MPI_Get_processor_name(aux3, &aux4); 
  MPI_Get_version (&aux5, &aux6);

  if (aux2 == 0) {
    printf("Há %d processos.\n", aux1);
    printf("Processador: %s, Número de caracteres: %d\n", aux3, aux4);
    printf("Versão: %d, Subversão: %d\n", aux5, aux6);
  }

  printf("Processo com ranque: %d\n", aux2);

  MPI_Finalize();

  return 0;
}