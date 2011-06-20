#pragma once
#ifndef IMAGE_PREDICTOR_H
#define IMAGE_PREDICTOR_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include"../rf_train./forest_id3.h"

#define MAX_DEPTHVALUE 300

class ImagePredictor
{
public:
	ImagePredictor(void);
	~ImagePredictor(void);

	void init();
	void createHash();

	void setForestParam( int tNum, int K);
	bool readForest(const char* filename);
	bool readData(const char* filename);
	bool readLabel(const char* filename);
	bool readParam(const char* filename);
	void setParameter( int w, int h, int rw, int rh);
	bool writeParam(const char* filename);
	bool writeForest(const char* filename);
	bool saveData(const char* filenam);
	bool saveLabel(const char* filename);

	bool predictData();
	int predictOnePixel( int xx, int yy);

	int color2label(int r, int g, int b);
	int label2color(int label);

private:
	int hashRGB[24];
	IplImage *data;
	IplImage *label;
	float offset[SEEDS_ARRAY_SIZE][2];
	ID3Forest forest;	
	int width;
	int height;
	int rectWidth;
	int rectHeight;
};


#endif