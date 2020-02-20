#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define N 1000
#define PI acos(-1)

double f(double x)
{
	return 4.0/(1.0+x*x);
}


int main(void)
{
int i,size,rank;
	MPI_Init(NULL,NULL);

	MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int chunk=N/size;
	
	double top=0.0;
	double h=1.0/(double)N;

	
	for(i=rank*chunk+1;i<=(rank+1)*chunk;i++)
		top+=f(i*h);
	top *=h;
	printf("Yaklaşık PI =%.16f\n",top);


	

/* Serial case
	for(i=1; i<=N; i++)
	{
		top+= f(i*h);
	}

	top *=h;
*/
	//printf("Gerçek PI =%.16f\n",PI);
	//printf("Yaklaşık PI =%.16f\n",top);

	MPI_Finalize();

}




