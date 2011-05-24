#include "pixelmanager.h"
#include "id3tree_gpu.h"



void createGPUForest( Forest *forest, float **a)
{
	int treeNum;
	int maxTreeNodeNum;
	int treeNodeSize;
	int i;
	int j;
	int k;

	treeNum = NUM_OF_TREES;
	maxTreeNodeNum = MAX_TREE_NODE_NUM;
	for( i=0; i<treeNum; i++) {
		if( maxTreeNodeNum < forest->forest[i].numOfNodes)
			maxTreeNodeNum = forest->forest[i].numOfNodes;
	}
	treeNodeSize = 5 + NUM_OF_CLASSES;

	*a = (float *)malloc(NUM_OF_TREES * maxTreeNodeNum * treeNodeSize * sizeof(float));

	for( i=0; i<treeNum; i++) {
		for( j=0; j<forest->forest[i].numOfNodes; j++) {
			(*a)[ i*(maxTreeNodeNum*treeNodeSize) + j*treeNodeSize + 0] = forest->forest[i].nodeArray[j].parent;
			(*a)[ i*(maxTreeNodeNum*treeNodeSize) + j*treeNodeSize + 1] = forest->forest[i].nodeArray[j].leftChild;
			(*a)[ i*(maxTreeNodeNum*treeNodeSize) + j*treeNodeSize + 2] = forest->forest[i].nodeArray[j].isLeaf;
			(*a)[ i*(maxTreeNodeNum*treeNodeSize) + j*treeNodeSize + 3] = forest->forest[i].nodeArray[j].attri;
			(*a)[ i*(maxTreeNodeNum*treeNodeSize) + j*treeNodeSize + 4] = forest->forest[i].nodeArray[j].thres;
			for( k=0; k<NUM_OF_CLASSES;k++) {
				(*a)[ i*(maxTreeNodeNum*treeNodeSize) + j*treeNodeSize + 4+k] = forest->forest[i].nodeArray[j].distribution[k];
			}
		}
	}
	/*
	printf( "%d ", a->parent);
	printf( "%d ", a->leftChild);
	printf( "%d ", a->isLeaf);
	printf( "%d ", a->attri);
	printf( "%f ", a->thres);
	for( i=0; i<NUM_OF_CLASSES;i++) {
	printf("%f ", a->distribution[i]);
	}
	printf( "\n");
	*/
}

void readParamToGPU( char *filename, int **a)
{
	FILE *pFile = NULL;
	int i;

	pFile = fopen(filename, "r");

	if(!pFile) return;
	*a = (int *)malloc(2*NUM_OF_PARAMS*sizeof(int));

	for( i=0; i<NUM_OF_PARAMS; i++) {
		fscanf(pFile, "%d %d", &((*a)[i*2]), &((*a)[i*2+1]));
	}
	fclose(pFile);
}

void createGPUImage( char *filename, float **a)
{
	FILE *pFile = NULL;
	int i;

	pFile = fopen(filename, "r");

	if(!pFile) return;
	*a = (float *)malloc(512*512*sizeof(float));

	for( i=0; i<512*512; i++) {
		fscanf(pFile, "%f", &((*a)[i]));
	}
	fclose(pFile);
}

__global__ void predictGPU( float* img, int* img_param, float * forest)
{
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int y = threadIdx.y + blockIdx.y * blockDim.y;
	float pixel = img[x*512+y];
	int iLevel;
	int ii;
	int iTree;
	bool run = true;
	float maxValue = -1;
	int maxLabel = -1;
	int blk = MAX_TREE_NODE_NUM*(5+NUM_OF_CLASSES);
	int lin = (5+NUM_OF_CLASSES);
	float dis[NUM_OF_CLASSES] = {0};

	run = pixel < 0.5? false:true;
	pixel = 255-pixel;

	/*
	p1 = (float)(((uchar*)(pImg->imageData + pImg->widthStep*yy))[xx*3]);
	if ( p1 < 0.5)
	continue;
	p1 = 255-p1;
	for ( int i=0; i<SEEDS_ARRAY_SIZE; i++) {
	//check
	u1 = xx + seedsX[i]/p1;
	if ( u1 < 0 || u1 >= width) 
	p2 = MAX_DEPTHVALUE;
	else 
	p2 = (float)(((uchar*)(pImg->imageData + pImg->widthStep*yy))[u1*3]);

	v1 = yy + seedsY[i]/p1;
	if ( v1 < 0 || v1 >= height)
	p3 = MAX_DEPTHVALUE;
	else
	p3 = (float)(((uchar*)(pImg->imageData + pImg->widthStep*yy))[v1*3]);

	p2 = p2<0.5? MAX_DEPTHVALUE: (255-p2);
	p3 = p3<0.5? MAX_DEPTHVALUE: (255-p3);
	feat = p2 - p3;
	outfile << feat << "\t";				
	}
	*/

	for(iTree = 0; run && iTree < NUM_OF_TREES; iTree++) {
		for( iLevel = 0; run;) {
			iLevel = forest[iTree*blk + iLevel*lin + 1];
			run = (forest[iTree*blk + iLevel*lin + 2] != 0);
		}
		run = true;
		for( ii = 0; ii < NUM_OF_CLASSES; ii ++) {
			dis[ii] += forest[iTree*blk + iLevel*lin + 4+ii];
		}
	}

	for( ii = 0; ii < NUM_OF_CLASSES; ii ++) 
		maxLabel = dis[ii] > maxValue? ii: maxLabel;

}

void predictCPU( float* img, int* img_param, float * forest)
{
	int xx;
	int yy;
	float pixel;
	int iLevel;
	int ii;
	int iTree;
	bool run = true;
	float maxValue = -1;
	int maxLabel = -1;
	int blk = MAX_TREE_NODE_NUM*(5+NUM_OF_CLASSES);
	int lin = (5+NUM_OF_CLASSES);
	float dis[NUM_OF_CLASSES] = {0};

	for(xx=0; xx<512; xx++) 
		for(yy=0; yy<512; yy++){
			pixel = img[xx*512+yy];
			run = true;
			maxValue = -1;
			maxLabel = -1;
			for( ii = 0; ii < NUM_OF_CLASSES; ii ++) 
				dis[ii] = 0;
			if(pixel < 0.5)
				run = false;
			pixel = 255-pixel;

			for(iTree = 0; run && iTree < NUM_OF_TREES; iTree++) {
				for( iLevel = 0; run;) {
					iLevel = forest[iTree*blk + iLevel*lin + 1];
					run = (forest[iTree*blk + iLevel*lin + 2] != 0);
				}
				run = true;
				for( ii = 0; ii < NUM_OF_CLASSES; ii ++) {
					dis[ii] += forest[iTree*blk + iLevel*lin + 4+ii];
				}
			}

			for( ii = 0; ii < NUM_OF_CLASSES; ii ++) 
				if(dis[ii] > maxValue) {
					maxLabel = ii;
				}
		}
}
