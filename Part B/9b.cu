%%cu

#include<stdio.h>
#define BLOCK_WIDTH 4
#define W 4

__global__ void matMul(double* a, double* b, double* c, int w)
{
    int row = threadIdx.x;
    int col = threadIdx.y;
    int value = 0;
    for(int i = 0; i < w; i++)
    {
        int a_var = a[col * w + i];
        int b_var = b[i * w + row];
        value += a_var * b_var;
    }
    c[col * w + row] = value;
}

int main()
{
    int i, size = W * W;
    double *h_a, *h_b, *h_c, *d_a, *d_b, *d_c;
 
    size_t bytes = size * sizeof(double);
    h_a = (double*)malloc(bytes);
    h_b = (double*)malloc(bytes);
    h_c = (double*)malloc(bytes);
    cudaMalloc(&d_a, bytes);
    cudaMalloc(&d_b, bytes);
    cudaMalloc(&d_c, bytes);
 
    for(i = 0; i < size; i++) h_a[i] = h_b[i] = i;
    
    printf("\n\nMatrix A:\n");
    for(i = 0; i < size; i++)
    {
        printf("%f\t", h_a[i]);
        if((i+1) % W == 0) printf("\n");
    }
 
    printf("\n\nMatrix B:\n");
    for(i = 0; i < size; i++)
    {
        printf("%f\t", h_b[i]);
        if((i+1) % W == 0) printf("\n");
    }
 
    cudaMemcpy(d_a, h_a, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, bytes, cudaMemcpyHostToDevice);

    dim3 threads(BLOCK_WIDTH, BLOCK_WIDTH);
    dim3 grid(W / threads.x, W / threads.y);
 
    matMul<<<grid, threads>>>(d_a, d_b, d_c, W);
 
    cudaMemcpy(h_c, d_c, bytes, cudaMemcpyDeviceToHost);
 
    printf("\n\nMatrix C:\n");
    for(i = 0; i < size; i++)
    {
        printf("%f\t", h_c[i]);
        if((i+1) % W == 0) printf("\n");
    }
 
    free(h_a);
    free(h_b);
    free(h_c);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
}
