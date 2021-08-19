/*
    This code is the example 3.18 from the textbook used in the course. 
    You can also find it in gpsilva2003 GitHub repository 
    (https://raw.githubusercontent.com/gpsilva2003/MPI/main/src/mpi_allreduce.c)

    What was modified for this exercise?
    1) Instead of using MPI_Allreduce, we are using MPI_Reduce + MPI_Bcast
    2) srand was modified to (meu_ranque+meu_ranque*meu_ranque)
    3) MPI_Wtime is being used to extract execution time
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"
#define NELEM 1024

int main(int argc, char *argv[]) { /* mpi_allreduce.c  */
int i, meu_ranque, num_procs;
float *nums_aleat = NULL;
float media, dif_quad_local = 0, soma_local = 0;
float soma_global, dif_quad_global, desvio_padrao;
double t0, t1;

   MPI_Init(&argc, &argv);

   t0 = MPI_Wtime();

   MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
   MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
   /* Alimenta o gerador de números aleatórios com valores diferentes para cada processo */
   //srand(MPI_Wtime()*(meu_ranque+1));
   srand(meu_ranque+meu_ranque*meu_ranque);
   /* Cria um vetor de números aleatórios em todos os processos. Cada número tem um valor entre 0 e 1 */
   nums_aleat  = (float *)malloc(sizeof(float) * NELEM);
   for (i = 0; i < NELEM; i++) 
        nums_aleat[i] = (rand() / (float)RAND_MAX);
   /* Soma os números localmente */
   for (i = 0; i < NELEM; i++) 
        soma_local += nums_aleat[i];
   /* Imprime a soma e média dos números aleatórios em cada processo */
   printf("Soma local para o processo %d - %f, media local = %f\n", meu_ranque, soma_local, soma_local / NELEM);
   /* Reduz todas as somas locais em uma soma global para poder calcular a média */
   //MPI_Allreduce(&soma_local, &soma_global, 1, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);
   MPI_Reduce(&soma_local, &soma_global, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
   MPI_Bcast(&soma_global, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
   media = soma_global / (NELEM * num_procs);
   /* Computa a soma local do quadrado das diferenças da média */
   for (i = 0; i < NELEM; i++) 
   dif_quad_local += (nums_aleat[i] - media) * (nums_aleat[i] - media);
   /* Reduz a soma global do quadrado das diferenças locais para o processo raiz imprimir a resposta */
   MPI_Reduce(&dif_quad_local, &dif_quad_global, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
   /* O desvio padrão é a raiz quadrada da média do quadrado das diferenças */
   if (meu_ranque == 0) {
       desvio_padrao = sqrt(dif_quad_global/(NELEM  * num_procs));
       printf("Média - %f, Desvio padrão  = %f\n", media, desvio_padrao);
   }
   /* Libera espaço do vetor */
   free(nums_aleat);

   t1 = MPI_Wtime();

   if (meu_ranque == 0) {
       printf("The program executed in %.4f seconds.\n", t1 - t0);
   }

   MPI_Finalize();
   return(0);
}