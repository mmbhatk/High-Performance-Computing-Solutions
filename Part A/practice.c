#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int i, n, *arr, max = 0, max_s = 0;

	printf("\nEnter the number of elements: ");
	scanf("%d", &n);

	arr = (int *)malloc(sizeof(int) * n);
	for(i = 0; i < n; i++) arr[i] = rand() % 1000;
	printf("\nThe array elements are: \n");
	for(i = 0; i < n; i++) printf("%d\t", arr[i]);

	omp_set_num_threads(8);

	// Parallel computation
	#pragma omp parallel for
	for(i = 0; i < n; i++)
	{
		if(arr[i] > max)
		{
			#pragma omp critical
			if(arr[i] > max) max = arr[i];
		}
	}

	//Serial computation
	for(i = 0; i < n; i++)
		if(arr[i] > max_s)
			max_s = arr[i];

	// Check for output validity
	if(max == max_s) printf("\nMax value is the same for serial and parallel computation.\n");
	else printf("\nMax value is not the same for serial and parallel computation.\n");

	printf("\nThe largest number in the given array is: %d\n", max);
	free(arr);
}
