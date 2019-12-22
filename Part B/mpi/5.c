#include <stdio.h>
#include <mpi.h>
#include <string.h>
#define BUFFER_SIZE 20

int main(int argc,char *argv[])
{
	int rank, size, i, root = 3;
	char msg[BUFFER_SIZE];

	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank == 3) 	
	{
		// system("hostname");
		strcpy(msg, "Hello ");
		for (i = 0; i < size; i++)
			if(i != root)
				MPI_Send(msg, BUFFER_SIZE, MPI_CHAR, i, 0, MPI_COMM_WORLD);
	}

	else
	{ 	
		//system("hostname");
		MPI_Recv(msg, BUFFER_SIZE, MPI_CHAR, root, 0, MPI_COMM_WORLD, &status);
		printf("\nReceived %s in process with rank %d from process with rank %d.\n", msg, rank, root);
	}
	MPI_Finalize();
	return 0;
}
