#include<iostream>
#include "id3tree_gpu.h"
#include "pixelmanager.h"
#include <stdio.h>
#include <cutil_inline.h>

int main()
{
	Forest frst;
	char filename[] = "data/000000.tree";
	char filenameParam[] = "data/000000.param";
	char filenameImg[] = "data/000000_color.float";

	float *frst_gpu;
	int *param_gpu;
	float *img_gpu;

	float *frst_device;
	int *param_device;
	float *img_device;

	unsigned int timer = 0;
	int treeSize = MAX_TREE_NODE_NUM*NUM_OF_TREES*(5+NUM_OF_CLASSES);

	printf("%s\n",filename);
	readForest(filename, &frst);

	
	//printForest(&frst);
	createGPUForest( &frst, &frst_gpu);
	createGPUImage( filenameImg, &img_gpu);
	readParamToGPU( filenameParam, &param_gpu);

	cutilCheckError( cutCreateTimer( &timer));
	/*	
	cutilCheckError( cutStartTimer( timer));

	printf("Processing time: %f (ms); TreeSize: %d\n", cutGetTimerValue( timer), treeSize);
	cudaMalloc(&frst_device, treeSize*sizeof(float));
	cudaMemcpy(frst_device, frst_gpu, treeSize*sizeof(float), cudaMemcpyHostToDevice );
	printf("Processing time: %f (ms)\n", cutGetTimerValue( timer));

	cudaMalloc(&param_device, NUM_OF_PARAMS*sizeof(int));
	cudaMemcpy(param_device, param_gpu, NUM_OF_PARAMS*sizeof(int), cudaMemcpyHostToDevice );
	printf("Processing time: %f (ms)\n", cutGetTimerValue( timer));

	cudaMalloc(&img_device, 512*512*sizeof(float));
	cudaMemcpy(img_device, img_gpu, 512*512*sizeof(float), cudaMemcpyHostToDevice );
	printf("Processing time: %f (ms)\n", cutGetTimerValue( timer));
	
	
	dim3 grids(32,32);
	dim3 threads(16,16);
	predictGPU<<<grids, threads>>>(img_device,param_device,frst_device);

	cutilCheckError( cutStopTimer( timer));
	printf("Processing time: %f (ms)\n", cutGetTimerValue( timer));


	*/
	cutilCheckError( cutResetTimer( timer));
	cutilCheckError( cutStartTimer( timer));
	predictCPU(img_gpu,param_gpu,frst_gpu);
	cutilCheckError( cutStopTimer( timer));
	printf("Processing time: %f (ms)\n", cutGetTimerValue( timer));
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