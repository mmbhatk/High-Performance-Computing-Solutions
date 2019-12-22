#include <stdio.h>
#include <mpi.h>

void main(int argc, char *argv[])
{
	int sc,rc,rank,size, m, param[10],i;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	sc = rc =1;
	m = 10 + rank;

	MPI_Gather(&m, sc, MPI_INT, param, rc, MPI_INT, 0, MPI_COMM_WORLD);

	if(rank == 0)
		for(i = 1; i < size; i++)
			printf("\nRank %d received param[%d] = %d", rank, i, param[i]);
	MPI_Finalize();
}
