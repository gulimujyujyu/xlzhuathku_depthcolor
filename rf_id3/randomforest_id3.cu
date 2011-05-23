#include "randomforest_id3.h"
#include <stdio.h>

__global__ void debugger( float *ptr) {
	int tid = blockIdx.x;
	if( tid < 25)
		ptr[tid] += 1;
}

void readTrainingSet(float **a, char *filename, int itemNum, int dim)
{
	FILE *file;
	file = fopen( filename, "r");

	*a = (float *)malloc( itemNum*(dim+1)*sizeof(float));

	for ( int i=0; i<itemNum; i++) {
		for ( int j=0; j<dim; j++) {
			fscanf( file, "%f", &((*a)[i*(dim+1)+j]));
			//printf( "%.2f ", (*a)[i*(dim+1)+j]);
		}
		fscanf( file, "%f", &((*a)[i*(dim+1)+dim]));
		//printf( "%.2f\n", (*a)[i*(dim+1)+dim]);
	}
	fclose(file);
}

float * createDevicePtr(float *a, int itemNum, bool needRandom, int dim)
{
	// Host code
	float *devPtr;
	float *b;
	b = (float *)malloc( itemNum*(dim+1)*sizeof(float));
	int width = (dim+1), height = itemNum;
	
	size_t pitch;
	cudaMalloc(&devPtr, width * height * sizeof(float));
	cudaMemcpy(devPtr, a,  width * height * sizeof(float), cudaMemcpyHostToDevice);
    
	for ( int i=0; i<itemNum; i++) {
		for ( int j=0; j<dim; j++) {
			printf( "%f ", a[i*(dim+1)+j]);
		}
		printf( "%f\n", a[i*(dim+1)+dim]);
	}
	//debugger<<<25,1>>>(devPtr);
	//cudaMemcpy(b, devPtr,  width * height * sizeof(float), cudaMemcpyDeviceToHost);
	//for ( int i=0; i<itemNum; i++) {
	//	for ( int j=0; j<dim; j++) {
	//		printf( "%f ", b[i*(dim+1)+j]);
	//	}
	//	printf( "%f\n", b[i*(dim+1)+dim]);
	//}
	return devPtr;
}