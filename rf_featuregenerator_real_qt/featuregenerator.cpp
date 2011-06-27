#include "featuregenerator.h"
#include <fstream>
#include <opencv/highgui.h>

int		R[] = {255,255,  0,  0,  0,255,255};
int		G[] = {  0,  0,  0,255,255,255,255};
int		B[] = {  0,255,255,  0,255,255,  0};
int label[] = {  0,  1,  2,  3,  4,  5,  6};

FeatureGenerator::FeatureGenerator(void)
{
	width = 512;
	height = 512;
	rectHeight = 512;
	rectWidth = 512;
	pImg = NULL;
	pImgLabel = NULL;
}

FeatureGenerator::~FeatureGenerator(void)
{
	outfile.close();
	outfileLabel.close();
	outfileParam.close();
	if(pImg)
		cvReleaseImage(&pImg);
	if(pImgLabel)
		cvReleaseImage(&pImgLabel);
}

void FeatureGenerator::createHash()
{
	for( int i=0; i<24; i++) {
		hashRGB[i] = R[i]*1000000 + G[i]*1000 + B[i];
	}
}

bool FeatureGenerator::read(const char * filename)
{
	if(pImg) {
		cvReleaseImage(&pImg);
	}
	pImg = cvLoadImage( filename, 1);
	if ( pImg == NULL) {
		return false;
	}
	return true;
}

bool FeatureGenerator::readLabel(const char * filename)
{
	if(pImgLabel) {
		cvReleaseImage(&pImgLabel);
	}
	pImgLabel = cvLoadImage( filename, 1);
	if ( pImgLabel == NULL) {
		return false;
	}
	return true;
}

bool FeatureGenerator::setOutputFilename(const char* filename, const char* filenameParam, int flag = 0)
{
	switch(flag) {
		case 0:
			outfile.open( filename, ios::out);
			outfileParam.open( filenameParam, ios::out);
			break;
		case 1:
			outfile.open( filename, ios::app);
			outfileParam.open( filenameParam, ios::app);
			break;
		default:
			return false;
	}
	return true;
}

bool FeatureGenerator::setOutputFilenameLabel(const char* filename, int flag = 0)
{
	switch(flag) {
		case 0:
			outfileLabel.open( filename, ios::out);
			break;
		case 1:
			outfileLabel.open( filename, ios::app);
			break;
		default:
			return false;
	}
	return true;
}

void FeatureGenerator::generateFeatures()
{
	if ( !(outfile.good()) || !(outfileParam.good())) {
		return ;
	}
	for( int ii = 0; ii<SEEDS_ARRAY_SIZE; ii++) {
		outfileParam << seedsX[ii] << "\t" << seedsY[ii] << endl;
	}
	float p1, p2, p3;
	float feat = 0;
	int u1, v1;
	for( int xx = 0; xx < width; xx += IMAGE_STEP) 
		for ( int yy =0; yy<height; yy += IMAGE_STEP) {
			//get element: depth;
			p1 = (float)(((uchar*)(pImg->imageData + pImg->widthStep*yy))[xx*3]);
			if ( p1 < 0.5)
				continue;
			p1 = 255-p1;
			for ( int i=0; i<SEEDS_ARRAY_SIZE; ) {
				//check
				u1 = xx + seedsX[i];
				v1 = yy + seedsY[i];
				if ( u1 < 0 || u1 >= width || v1 < 0 || v1 >= height) 
					p2 = MAX_DEPTHVALUE;
				else 
					p2 = (float)(((uchar*)(pImg->imageData + pImg->widthStep*(v1)))[(u1)*3]);
				i++;

				u1 = xx + seedsX[i];
				v1 = yy + seedsY[i];
				if ( u1 < 0 || u1 >= width || v1 < 0 || v1 >= height)
					p3 = MAX_DEPTHVALUE;
				else
					p3 = (float)(((uchar*)(pImg->imageData + pImg->widthStep*(v1)))[(u1)*3]);
				i++;

				p2 = p2<0.5? MAX_DEPTHVALUE: (255-p2);
				p3 = p3<0.5? MAX_DEPTHVALUE: (255-p3);
				feat = p2 - p3;
				outfile << feat << "\t";				
			}
			outfile << endl;
		}
}

void FeatureGenerator::generateLabels()
{
	if ( !(outfileLabel.good())) {
		return ;
	}
	float p1, p2, p3;
	float feat = 0;
	int u1, v1;
	int ii;
	for( int xx = 0 ; xx < width; xx += IMAGE_STEP) 
		for ( int yy =0; yy<height; yy += IMAGE_STEP) {
			//get element: depth;
			p1 = (float)(((uchar*)(pImg->imageData + pImg->widthStep*yy))[xx*3]);
			if ( p1 < 0.5)
				continue;
			p1 = (int)(((uchar*)(pImgLabel->imageData + pImgLabel->widthStep*yy))[xx*3+2]);
			p2 = (int)(((uchar*)(pImgLabel->imageData + pImgLabel->widthStep*yy))[xx*3+1]);
			p3 = (int)(((uchar*)(pImgLabel->imageData + pImgLabel->widthStep*yy))[xx*3]);
			int RGB = p1*1000000 + p2*1000+ p3;
			for( ii = 0; ii<NUM_OF_LABELS; ii++) {
				if(RGB == hashRGB[ii])
					break;
			}
			outfileLabel << (ii>=NUM_OF_LABELS?(-1):(label[ii])) << endl;
		}
}

void FeatureGenerator::setParameter(int w, int h, int rw, int rh)
{
	this->width = w;
	this->height = h;
	this->rectWidth = rw;
	this->rectHeight = rh;
}

/*
*	MUST CALL AFTER setParameter
*/
void FeatureGenerator::setSeeds(int a[SEEDS_ARRAY_SIZE], int b[SEEDS_ARRAY_SIZE])
{
	int i;
	for( i=0; i<SEEDS_ARRAY_SIZE; i++) {
		int u = a[i]%rectWidth - rectWidth/2;
		int v = b[i]%rectHeight - rectHeight/2;

		this->seedsX[i] = u;
		this->seedsY[i] = v;
	}
}