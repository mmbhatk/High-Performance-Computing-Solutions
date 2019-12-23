#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int tid, x = 0;

	#pragma omp parallel shared(x)
	{
		tid = omp_get_thread_num();

		#pragma omp critical
		x = x + 1;

		printf("\n[%d]\tx = %d", tid, x);
	}
}
