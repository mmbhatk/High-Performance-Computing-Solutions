#include <stdio.h>
#include <mpi.h>

int main(int argc,char *argv[])
{
	int i, rank, size, value, sum = 0;
	int Source, Destination;
	MPI_Status status;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(rank == 0)
	{
		for(i = 1 ; i < size ; i++)
		{
			Source = i;
			MPI_Recv(&value, 1, MPI_INT, Source, 0, MPI_COMM_WORLD, &status);
			sum = sum + value;
		}
		printf("MyRank = %d, SUM = %d\n", rank, sum);
	}

	else
	{
		Destination = 0;
		MPI_Send(&rank, 1, MPI_INT, Destination, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();

}
