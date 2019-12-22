#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#define N 1000

int main(int argc, char* argv[])
{
	int i, a[N], b[N], sum = 0;

	for(i = 0; i < N; i++) a[i] = b[i] = i;

	#pragma omp parallel for reduction(+: sum)
	for(i = 0; i < N; i++)
		sum = sum + (a[i] + b[i]);
	printf("\nSum = %d\n", sum);
}
