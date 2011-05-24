#pragma once

#ifndef IMAGEGENERATOR_H
#define IMAGEGENERATOR_H

#include <opencv/cv.h>
#include <fstream>
#define SEEDS_ARRAY_SIZE 500
#define SEEDS_PER_IMAGE 2000
#define MAX_DEPTHVALUE 300
#define IMAGE_STEP 2
using namespace std;

class FeatureGenerator
{
public:
	FeatureGenerator(void);
	~FeatureGenerator(void);
	bool read( const char * filename);
	bool readLabel( const char * filename);
	void setParameter( int w, int h, int rw, int rh);
	void setSeeds( int a[SEEDS_ARRAY_SIZE], int b[SEEDS_ARRAY_SIZE]);
	void generateFeatures();
	void generateLabels();
	bool setOutputFilename( const char* filename, const char* filenameParam, int flag);
	bool setOutputFilenameLabel( const char* filename, int flag);
	void createHash();
private: 
	IplImage* pImg;
	IplImage* pImgLabel;
	ofstream outfile;
	ofstream outfileParam;
	ofstream outfileLabel;
	int width;
	int height;
	int rectWidth;
	int rectHeight;
	int seedsX[SEEDS_ARRAY_SIZE];
	int seedsY[SEEDS_ARRAY_SIZE];
	int hashRGB[24];
};
#endif
