#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

#define NRA 5
#define NCA 5
#define NCB 5

int main(int argc, char* argv[])
{
	int i, j, k, tid, chunk, nthreads;
	double a[NRA][NCA], b[NCA][NCB], c[NRA][NCB];
	chunk = 2;

	#pragma omp parallel shared(a, b, c, nthreads, chunk) private(i, j, k, tid)
	{
		tid = omp_get_thread_num();
		if(tid == 0)
		{
			nthreads = omp_get_num_threads();
			printf("\nNumber of threads: %d", nthreads);
			printf("\nInitializing matrices.");
		}

		#pragma omp for schedule(static, chunk)
		for(i = 0; i < NRA; i++)
			for(j = 0; j < NCA; j++)
				a[i][j] = 1;

		#pragma omp for schedule(static, chunk)
		for(i = 0; i < NCA; i++)
			for(j = 0; j < NCB; j++)
				b[i][j] = 1;

		#pragma omp for schedule(static, chunk)
		for(i = 0; i < NRA; i++)
			for(j = 0; j < NCB; j++)
				c[i][j] = 0;

		#pragma omp for schedule(static, chunk)
		for(i = 0; i < NRA; i++)
		{
			printf("\nThread [%d] did row %d.", tid, i);
			for(j = 0; j < NCB; j++)
				for(k = 0; k < NCA; k++)
					c[i][j] += a[i][k] * b[k][j];
		}
	}

	printf("\n\nMatrix A:\n");
	for(i = 0; i < NRA; i++)
	{
		for(j = 0; j < NCA; j++) printf("%f\t", a[i][j]);
		printf("\n");
	}

	printf("\n\nMatrix B:\n");
	for(i = 0; i < NCA; i++)
	{
		for(j = 0; j < NCB; j++) printf("%f\t", b[i][j]);
		printf("\n");
	}

	printf("\n\nMatrix c:\n");
	for(i = 0; i < NRA; i++)
	{
		for(j = 0; j < NCB; j++) printf("%f\t", c[i][j]);
		printf("\n");
	}
}
