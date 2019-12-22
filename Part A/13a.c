#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	int nthreads, tid, procs, maxt, inpar, dynamic, nested;

	#pragma omp parallel private(nthreads, tid)
	{
		tid = omp_get_thread_num();
		if (tid == 0)
		{
	 		printf("Thread %d getting environment info...\n", tid);
	 		procs = omp_get_num_procs();
			//Number of processors
	 		nthreads = omp_get_num_threads();
			//Number of threads
	 		maxt = omp_get_max_threads();
			//Maximum number of threads
	 		inpar = omp_in_parallel();
			//omp_set_dynamic(1);	
			dynamic = omp_get_dynamic();
	 		nested = omp_get_nested();

	 		/* Print environment information */
	 		printf("Number of processors = %d\n", procs);
	 		printf("Number of threads = %d\n", nthreads);
	 		printf("Max threads = %d\n", maxt);
	 		printf("In parallel? = %d\n", inpar);
	 		printf("Dynamic threads enabled? = %d\n", dynamic);
	 		printf("Nested parallelism supported? = %d\n", nested);
		}
	}
}
