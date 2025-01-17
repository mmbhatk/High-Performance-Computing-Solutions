#include <stdio.h>
#include <omp.h>
#include <malloc.h>
#include <stdlib.h>
#define N 100000000
#define TRUE 1
#define FALSE 0

int main(int argc, char **argv )
{
	char host[80];
	int *a;
	int i, k, threads, pcount;
	double t1, t2;
	int found;

	a = (int *) malloc((N+1) * sizeof(int));
	for(i = 2; i<=N; i++) a[i] = 1;
	k = 2;

	t1 = omp_get_wtime();

	#pragma omp parallel firstprivate(k) private(i, found)
	while (k*k <= N)
	{
		#pragma omp for
		for (i=k*k; i<=N; i+=k) a[i] = 0;
		found = FALSE;
		for (i=k+1;!found;i++)
		{
			if (a[i])
			{
				k = i;
				found = TRUE;
			}
		}
	}

	t2 = omp_get_wtime();
	printf("%.2f seconds\n",t2-t1);

	pcount = 0;
	for (i=2; i <= N; i++)
		if(a[i]) pcount++;
	printf("%d primes between 0 and %d\n",pcount,N);
}
