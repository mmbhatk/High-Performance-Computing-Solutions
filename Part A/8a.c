#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main()
{
	int n, *arr, i, max, c;
	omp_lock_t MAXLOCK;

	printf("\nEnter the number of elements: \n");
	scanf("%d", &n);

	if(n <= 0) {printf("\nArray elements cannot be stored.\n"); exit(1);}

	arr = (int *) malloc(sizeof(int) * n);
	for(int i = 0; i < n; i++) arr[i] = rand() % 1000;
	printf("\nThe array elements are:\n");
	for(int i = 0; i < n; i++) printf("%d\t", arr[i]);

	if(n == 1) {printf("\nLargest element: %d", arr[0]); exit(1);}

	// Parallel calculation
	printf("\nLocking...\n");
	omp_init_lock(&MAXLOCK);
	omp_set_num_threads(8);

	max = 0;
	#pragma omp parallel for
	for(i = 0; i < n; i++)
	{
		if(arr[i] > max)
		{
			omp_set_lock(&MAXLOCK);
			if(arr[i] > max) max = arr[i];
			omp_unset_lock(&MAXLOCK);
		}
	}
	omp_destroy_lock(&MAXLOCK);

	// Serial calculation
	c = arr[0];
	for(i = 1; i < n; i++)
		if(arr[i] > c)
			c = arr[i];

	printf("\nmax = %d", max);
	printf("\nc = %d", c);
	free(arr);
}


/*
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main()
{
	int *array, i, N, max, c;
	omp_lock_t MAXLOCK;

	printf("Enter the number of elements\n");
	scanf("%d", &N);

	if (N <= 0)
	{
		printf("The array elements cannot be stored\n");
		exit(1);
	}

	array = (int *) malloc(sizeof(int) * N);
	for (i = 0; i < N; i++) array[i] = rand()%1000;

	if (N == 1)
	{
		printf("The Largest Element In The Array Is %d", array[0]);
		exit(1);
	}

	// Parallel Calc
	printf("locking ..\n");
	omp_set_num_threads(8);
	omp_init_lock(&MAXLOCK);
	max = 0;
	printf("lock initialized\n");

	#pragma omp parallel for
	for (i = 0; i < N; i = i + 1)
	{
		if (array[i] > max)
		{
			omp_set_lock(&MAXLOCK);
			if (array[i] > max)
				max = array[i];
			omp_unset_lock(&MAXLOCK);
		}
	}
	omp_destroy_lock(&MAXLOCK);

	// Serial Calculation 
	c = array[0];
	for (i = 1; i < N; i++)
		if (array[i] > c)
			c = array[i];

	printf("The Array Elements Are \n");
	for (i = 0; i < N; i++)
	printf("%d\t", array[i]);
	printf("\n");

	// Compare
	if (c == max) printf("\nThe Max Value Is Same For Serial And Using Parallel OpenMP Directive\n");
	else
	{
		printf("\nThe Max Value Is NOT Same In Serial And Using Parallel OpenMP Directive\n");
		exit(1);
	}

	free(array);
	printf("\nThe Largest Number Of The Array Is %d\n", max);
}
*/
