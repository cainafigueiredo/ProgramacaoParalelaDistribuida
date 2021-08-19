/*

    Some parameters and variables of this program were hardcoded since the purpose of this exercise is 
    only to implement a piece of code to print the information about who sent the message, what was the tag
    and what was the number of elements that were sent given the following line of code:
    MPI_Recv(&vetor, MAX_FLOAT, MPI_FLOAT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);

*/

#include "mpi.h"
#include <stdio.h>
#define MAX_FLOAT 5

int main(int argc, char *argv[]) {

    int num_procs, meu_ranque, total_num, etiq = 3, destino = 0;
    float vetor[MAX_FLOAT] = {1,2,3,4,5};
    MPI_Status estado;

    MPI_Init(&argc, &argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    if (meu_ranque != 0) {
        MPI_Send(&vetor, MAX_FLOAT, MPI_FLOAT, destino, etiq, MPI_COMM_WORLD);
    }
    else {
        MPI_Recv(&vetor, MAX_FLOAT, MPI_FLOAT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);
    
        MPI_Get_count(&estado, MPI_FLOAT, &total_num);

        // Printing required information
        printf("O processo que enviou a mensagem foi: %d\n", estado.MPI_SOURCE);
        printf("A etiqueda da mensagem é: %d\n", estado.MPI_TAG);
        printf("Foram recebidos %d elementos\n", total_num);
    }

    MPI_Finalize();
    return 0;
}