#include <stdio.h>

// __global__ is a C language construct called a "Declaration Specifier" or "DecelSpec" 
// this tells CUDA that this is a kernel not CPU code
__global__ void square(float *d_out, float *d_in)
{
	int idx = threadIdx.x; // get index of the thread
	float f = d_in[idx];
	d_out[idx] = f * f;
}

int main(int argc, char** argv)
{
	const int ARRAY_SIZE = 64;
	const int ARRAY_BYTES = ARRAY_SIZE * sizeof(float);

	// generate input array on host
	float h_in[ARRAY_SIZE];
	for (int i = 0; i < ARRAY_SIZE; ++i)
	{
		h_in[i] = float(i);
	}
	float h_out[ARRAY_SIZE];

	// declare GPU memory pointers
	float * d_in;
	float * d_out;

	// allocate GPU memory
	cudaMalloc((void **) &d_in, ARRAY_BYTES);
	cudaMalloc((void **) &d_out, ARRAY_BYTES);

	// copy array from host to device
	cudaMemcpy(d_in, h_in, ARRAY_BYTES, cudaMemcpyHostToDevice);

	// launch kernel
	square<<<1, ARRAY_SIZE>>>(d_out, d_in);

	// copy array back from device to host
	cudaMemcpy(h_out, d_out, ARRAY_BYTES, cudaMemcpyDeviceToHost);

	// print results
	for(int i = 0; i < ARRAY_SIZE; ++i)
	{
		printf("%f", h_out[i]);
		printf(((i%4)!=3)?"\t":"\n");
	}

	// free GPU memory
	cudaFree(d_in);
	cudaFree(d_out);

	return 0;
}
