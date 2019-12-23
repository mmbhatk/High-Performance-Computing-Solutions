%%cu

#include <stdio.h>

__global__ void LM(float x)
{
	float f = x; 	 
}


__global__ void GM(float *array)
{
	array[threadIdx.x] = 1.0 * (float)threadIdx.x;
}


__global__ void SM(float *array)
{
	int i, index = threadIdx.x;
	float average, sum = 0.0;
 
	 __shared__ float shared_arr[128];
	shared_arr[index] = array[index];
 
	__syncthreads();

  	for(i = 0; i <= index; i++) sum += shared_arr[i];

  	average = sum / (index + 1);
	printf("Thread id = %d\t Average = %f\n", index, average);
}

int main(int argc, char **argv)
{
  	float h_arr[128], *d_arr;
    	size_t bytes = 128 * sizeof(float);
	cudaMalloc(&d_arr, bytes);
 
	LM<<<1, 128>>>(2.0);
 
	cudaMemcpy(d_arr, h_arr, bn, cudaMemcpyHostToDevice);
	GM<<<1, 128>>>(d_arr);
  
	cudaMemcpy(h_arr, d_arr, sizeof(float) * 128, cudaMemcpyDeviceToHost);
	SM<<<1, 128>>>(d_arr);

	cudaDeviceSynchronize();
}
