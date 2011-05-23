#ifndef RANDOMFOREST_ID3_H
#define RANDOMFOREST_ID3_H

#define SEEDS_ARRAY_SIZE 2000

struct RGImage {

};

//I/O
void readTrainingSet(float **a, char *filename, int itemNum, int dim);
float * createDevicePtr(float *a, int itenNum, bool needRandom, int dim);
//void writeTrainingSet(RFTrainingSet *a, char *filename, int itemNum);
#endif