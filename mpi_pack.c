#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int dogum_tarihi[3]={1,1,1995};
    char isim[30]="fatih mehmet ergin";
    float boy_agirlik[2]={1.79,82.3};
    char buffer[110];
    int position = 0;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size < 2)
    {
        printf("Please run with 2 processes.\n");fflush(stdout);
        MPI_Finalize();
        return 1;
    }
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        MPI_Pack(&dogum_tarihi, 1, MPI_INT, buffer, 110, &position, MPI_COMM_WORLD);
        MPI_Pack(isim, 100, MPI_CHAR, buffer, 110, &position, MPI_COMM_WORLD);
        MPI_Pack(&boy_agirlik, 1, MPI_FLOAT, buffer, 110, &position, MPI_COMM_WORLD);
        MPI_Send(buffer, position, MPI_PACKED, 1, 100, MPI_COMM_WORLD);
    }

    if (rank == 1)
    {
        MPI_Recv(buffer, 110, MPI_PACKED, 0, 100, MPI_COMM_WORLD, &status);
        MPI_Unpack(buffer, 110, &position, &dogum_tarihi, 1, MPI_INT, MPI_COMM_WORLD);
        MPI_Unpack(buffer, 110, &position, isim, 100, MPI_CHAR, MPI_COMM_WORLD);
        MPI_Unpack(buffer, 110, &position, &boy_agirlik, 1, MPI_FLOAT, MPI_COMM_WORLD);
       //printf("isim: %s ,dogum tarihi: %d.%d.%d ",isim,dogum_tarihi[0],dogum_tarihi[1],dogum_tarihi[2]);
        printf("isim: %s\ndogum tarihi: %d.%d.%d ",isim,dogum_tarihi[0],dogum_tarihi[1],dogum_tarihi[2]);
        printf("\nboy: %f\n",boy_agirlik[0]);
      // printf("%d\n,%d",sizeof(MPI_DOUBLE),sizeof(MPI_FLOAT));
       fflush(stdout);
    }

    MPI_Finalize();
    return 0;
}