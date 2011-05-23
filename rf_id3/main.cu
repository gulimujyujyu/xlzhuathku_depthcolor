#include<iostream>
#include "randomforest_id3.h"
#include "id3tree.h"
#include <stdio.h>

__global__ void kernel(void) {
}

int main()
{
	float *tptr;
	float *devPtr;
	char filename[] = "test.txt";
	int dim = 9;
	int itemNum = 5;
	readTrainingSet( &tptr, filename, itemNum, dim);
	//
	//for ( int i=0; i<itemNum; i++) {
	//	for ( int j=0; j<dim; j++) {
	//		printf( "%f ", tptr[i*(dim+1)+j]);
	//	}
	//	printf( "%f\n", tptr[i*(dim+1)+dim]);
	//}
	devPtr = createDevicePtr( tptr, itemNum, false, dim);

	Forest forest;
	trainForest( &forest, devPtr,itemNum, dim);

	return 0;
}

/*
int main()
{
	//STEP1: read images
	
	//STEP2: train random forest classifier

	//STEP3: test classifier
	kernel<<<1,1>>>();
	printf("Hello world!\n");

	int count;
	cudaGetDeviceCount(&count);
	printf("Count:\t%d\n", count);

	cudaDeviceProp prop;
	for( int i=0; i<count; i++) {
		cudaGetDeviceProperties(&prop,i);
		//print info
		printf("Name:\t%s\n", prop.name);
		printf("Global Mem:\t%d\n", prop.totalGlobalMem);
		printf("Const Mem:\t%d\n", prop.totalConstMem);
		printf("Shared Mem:\t%d\n", prop.sharedMemPerBlock);
		printf("Mem Pitch:\t%d\n", prop.memPitch);
		printf("Max Threads:\t%d\n", prop.maxThreadsPerBlock);
		printf("Compute Capasity:\t%d,%d\n", prop.minor, prop.major);
		printf("Processor Num:\t%d,%d\n", prop.multiProcessorCount);
	}
	return 0;
}
*/