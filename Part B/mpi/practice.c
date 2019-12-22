#include<stdio.h>
#include<mpi.h>

int main(int argc, char* argv[])
{
	int rank, size, i;
	int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Scatter((void *)data, 1, MPI_INT, (void *)&i, 1, MPI_INT, 0, MPI_COMM_WORLD);

	printf("\n[%d] Data: %d", rank, i);
	MPI_Finalize();
}
