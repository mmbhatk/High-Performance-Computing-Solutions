#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#define N 100000000

int main()
{
	int i, p = 2, count, *prime;
	double t1, t2;

	prime = (int *)malloc((N+1) * sizeof(int));
	for(i = 0; i < N; i++) prime[i] = 1;

	printf("\nMaximum number of threads: %d\n", omp_get_max_threads());

	t1 = omp_get_wtime();

	#pragma omp parallel firstprivate(p) private(i)
	while(p * p <= N)
	{
		if(prime[p] == 1)
			#pragma omp for
			for(i = p * p; i <= N; i += p) prime[i] = 0;
		p += 1;
	}

	t2 = omp_get_wtime();
	printf("\nTime taken: %.2f seconds\n", t2 - t1);

	count = 0;
	for(i = 2; i < N; i++)
		if(prime[i]) count++;

	printf("\n%d primes between 0 and %d", count, N);
}
