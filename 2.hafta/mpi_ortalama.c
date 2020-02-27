#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 10000
#define MASTER 0

float *create1DArray(int n)
{

    float *T=(float *)malloc(n*sizeof(int));
    return T;
}
int main(void)
{

int rank,size,i;
MPI_Init(NULL,NULL);
MPI_Status status;

MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);

int chunk= N/size;

float local_toplam=0.0;
float toplam=0.0;

float *dizi;
float *local_dizi;

if (rank == MASTER)
{
    dizi=create1DArray(N);
    local_dizi=create1DArray(chunk);
    for (i=0;i<N;i++)
        dizi[i]=1.0;
}
else
{
    local_dizi=create1DArray(chunk);
}

MPI_Scatter(dizi,chunk,MPI_FLOAT,local_dizi,chunk,MPI_FLOAT,MASTER,MPI_COMM_WORLD);

for(i=0;i<chunk;i++)
    local_toplam+=local_dizi[i];

MPI_Reduce(&local_toplam,&toplam,1,MPI_FLOAT, MPI_SUM,MASTER,MPI_COMM_WORLD);

if (rank==MASTER)
    printf("ortalama =%f\n",(toplam/N));


}
