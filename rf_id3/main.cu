#include<iostream>
#include "id3tree_gpu.h"
#include <stdio.h>

__global__ void kernel(void) {
}

int main()
{
	Forest frst;
	char filename[] = "data/000000.tree";

	printf("%s\n",filename);
	readForest(filename, &frst);
	printForest(&frst);

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