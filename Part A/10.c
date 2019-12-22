#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
	int i;

	omp_set_num_threads(2);

	#pragma omp parallel private(i)
	{
		int tid = omp_get_thread_num();
		int letters_per_thread = 26 / omp_get_num_threads();

		int start_letter = 'a' + letters_per_thread * tid;
		int end_letter = 'a' + letters_per_thread * (tid + 1);
		for(i = start_letter; i < end_letter; i++)
			printf("\n[%d]: %c", tid, i);
	}
}

