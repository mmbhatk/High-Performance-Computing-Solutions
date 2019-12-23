#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUFFER_SIZE 20

int main(int argc, char* argv[])
{
	int rank;
	char msg[BUFFER_SIZE];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank == 0) strcpy(msg, "Hello, World!\n");

	MPI_Bcast(msg, BUFFER_SIZE, MPI_CHAR, 0, MPI_COMM_WORLD);
	printf("\n[%d] %s", rank, msg);

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
}
