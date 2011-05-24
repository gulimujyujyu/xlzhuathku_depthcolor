#ifndef PIXELMANAGER_H
#define PIXELMANAGER_H

#include "id3tree_gpu.h"

void createGPUForest( Forest *forest);
void readParamToGPU( char *filename);
void readImageToGPU( char *filename);

void predict();
void showResult();
#endif