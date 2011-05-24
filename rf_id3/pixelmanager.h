#ifndef PIXELMANAGER_H
#define PIXELMANAGER_H

#include "id3tree_gpu.h"

void createGPUForest( Forest *forest, float **a);
void readParamToGPU( char *filename, int **a);
void createGPUImage( char *filename, float **a);

////////////////////////////////////////////////////////////////////////////////
//! Transform an image using texture lookups
//! @param g_odata  output data in global memory
////////////////////////////////////////////////////////////////////////////////
__global__ void predictGPU( float* img, int* img_param, float * forest);
void predictCPU( float* img, int* img_param, float * forest);

//void showResult();
#endif