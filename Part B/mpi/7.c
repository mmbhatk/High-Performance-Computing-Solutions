#include <stdio.h>
#include <mpi.h>

int main (int argc, char *argv[])
{

	int data[] = {1, 2, 3, 4, 5, 6, 7};
	// Size must be >= number of processors
	int rank, i = -1;

	MPI_Init (&argc, &argv);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	MPI_Scatter((void *)data, 1, MPI_INT, (void *)&i, 1, MPI_INT, 0, MPI_COMM_WORLD);

	printf ("[%d] Received i = %d\n", rank, i);
	MPI_Finalize();
}
