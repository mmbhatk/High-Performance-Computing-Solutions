#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
	int i, n, *arr, max = 0, max_s = 0;
	omp_lock_t MAXLOCK;

	printf("\nEnter the number of elements: ");
	scanf("%d", &n);

	arr = (int *)malloc(sizeof(int) * n);
	for(i = 0; i < n; i++) arr[i] = rand() % 1000;
	printf("\nArray elements are: \n");
	for(i = 0; i < n; i++) printf("%d\t", arr[i]);
	
	// Parallel computation
	omp_set_num_threads(8);
	omp_init_lock(&MAXLOCK);

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

	// Serial computation
	for(i = 0; i < n; i++)
		if(arr[i] > max_s)
			max_s = arr[i];


	// Check the output validity
	if(max == max_s) printf("\nMax value is the same for serial and parallel computation.\n");
	else printf("\nMax value is not the same for serial and parallel computation.\n");

	printf("\nThe largest number in the array is: %d\n", max);
	free(arr);
}
