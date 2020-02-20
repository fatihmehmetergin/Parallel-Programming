#include <stdio.h>
#include "mpi.h"
#define MASTER 0
void printArray(int *d,	int n)
{
	for (int i=0; i<n; i++)
	{
		printf("%d\t",d[i]);
	}
printf("\n");

}


int main(void) 
{

    MPI_Init(NULL, NULL);
	MPI_Status *stat;
	
    int size, rank;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank==MASTER)
	{
		int dizi[60];
		for(int i=0;i<60;i++)
		{
			dizi[i]=i+1;
		}
		MPI_Send(&dizi[15],15,MPI_INT,1,777,MPI_COMM_WORLD);
		MPI_Send(&dizi[30],15,MPI_INT,2,778,MPI_COMM_WORLD);
		MPI_Send(&dizi[45],15,MPI_INT,3,779,MPI_COMM_WORLD);

	}
	else
	{
	int altdizi[15];
	for (int i =0; i<15; i++)
	{
	altdizi[i]=0;
	}

	MPI_Recv(altdizi,15,MPI_INT,0,777,MPI_COMM_WORLD,stat);
	MPI_Recv(altdizi,15,MPI_INT,0,778,MPI_COMM_WORLD,stat);
	MPI_Recv(altdizi,15,MPI_INT,0,779,MPI_COMM_WORLD,stat);
	}		

	MPI_Finalize();

}
