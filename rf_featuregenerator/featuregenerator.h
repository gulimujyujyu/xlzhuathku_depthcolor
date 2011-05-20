#pragma once

#ifndef IMAGEGENERATOR_H
#define IMAGEGENERATOR_H

#include <stdio.h>
#include <opencv/cv.h>
#define SEEDS_ARRAY_SIZE 2000
#define MAX_DEPTHVALUE 300
class FeatureGenerator
{
public:
	FeatureGenerator(void);
	~FeatureGenerator(void);
	bool read( const char * filename);
	void setParameter( int w, int h, int rw, int rh);
	void setSeeds( int a[SEEDS_ARRAY_SIZE], int b[SEEDS_ARRAY_SIZE]);
	void generateFeatures();
	bool setOutputFilename( const char* filename, int flag);

private: 
	IplImage* pImg;
	FILE * outfile;
	int width;
	int height;
	int rectWidth;
	int rectHeight;
	int seedsX[SEEDS_ARRAY_SIZE];
	int seedsY[SEEDS_ARRAY_SIZE];
};
#endif
