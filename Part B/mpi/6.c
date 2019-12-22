#include <stdio.h>
#include <string.h>
#include <mpi.h>

void main(int argc, char *argv[])
{
	int rank, size, sndcnt = 5, rcvcnt, i, j;
	char mine[10], param[10][10];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	strcpy(mine, "Hello\0");
	if(rank==0) rcvcnt = 5;

	MPI_Gather(&mine, sndcnt, MPI_CHAR, param, rcvcnt, MPI_CHAR, 0, MPI_COMM_WORLD);

	if(rank==0)
		for(i = 0; i < size; i++)
		{
			printf("\n[%d] param[%d] = ", rank, i);
			for(j = 0; j < 5; j ++) printf("%c", param[i][j]);
		}
	MPI_Finalize();
}
