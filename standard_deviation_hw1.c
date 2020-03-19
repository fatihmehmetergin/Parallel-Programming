#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mpi.h" //MPI kutuphanesi

#define N 3000000
#define MASTER 0

double *create1DArray(int n) 
{
     double *T = (double *)malloc(n * sizeof(double));
     return T;
}

int main(void) {

int rank, size, i;
double baslangic,bitis;


MPI_Init(NULL, NULL);

MPI_Status status;

baslangic = MPI_Wtime();

MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);

int chunk = N / size;

double local_toplam = 0.0;
double toplam = 0.0;

// Initialization
double *dizi;
double *local_dizi;

if (rank == MASTER) {
    dizi = create1DArray(N);
    local_dizi = create1DArray(chunk);

    for (i = 0; i < N; i++)
{
        srand(time(NULL));
        dizi[i] = rand()%58;
}

} else {
    local_dizi = create1DArray(chunk);
}

// Scatter (data distribution)
MPI_Scatter(dizi, chunk, MPI_DOUBLE, local_dizi, chunk, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);

// Local computation
for (i = 0; i < chunk; i++)
    local_toplam += local_dizi[i];
    
// Gather data with reduction
MPI_Reduce(&local_toplam, &toplam, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);

double ort = toplam / N;

// MASTER prints out the average
if (rank == MASTER)
    printf("Ortalama = %f\n", ort);


MPI_Bcast(&ort, 1, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
double a=0.0;
double toplam_al=0.0;
double variance=0.0;
// Local computation FOR VAR
for (i = 0; i < chunk; i++)
{
    a=local_dizi[i]-ort;
    variance=variance+(a*a);
}
variance=variance/(N-1);

MPI_Reduce(&variance, &toplam_al, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);

if (rank == MASTER)
{
   printf("Standart Sapma = %f\nVariance Toplam = %f\n", sqrt(toplam_al),toplam_al);
}
bitis=MPI_Wtime();     

printf("MPI_Wtime : %1.4f\n", bitis-baslangic);
    fflush(stdout);

MPI_Finalize();

}







