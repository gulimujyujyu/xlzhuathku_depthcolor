#include "featuregenerator.h"
#include <stdio.h>
#include <opencv/highgui.h>

FeatureGenerator::FeatureGenerator(void)
{
	width = 512;
	height = 512;
	rectHeight = 512;
	rectWidth = 512;
	outfile = NULL;
	pImg = NULL;
}

FeatureGenerator::~FeatureGenerator(void)
{
	fclose(outfile);
}

bool FeatureGenerator::read(const char * filename)
{
	pImg = cvLoadImage( filename, 1);
	if ( pImg == NULL) {
		return false;
	}
	return true;
}

bool FeatureGenerator::setOutputFilename(const char* filename, int flag = 0)
{
	switch(flag) {
		case 0:
			outfile = fopen( filename, "w");
			break;
		case 1:
			outfile = fopen( filename, "a");
			break;
		default:
			return false;
	}
	return true;
}

void FeatureGenerator::generateFeatures()
{
	float p1, p2, p3;
	float feat;
	int u1, v1;
	for( int xx = 0 ; xx < width; xx++) 
		for ( int yy =0; yy<height; yy++) {
			for ( int i=0; i<SEEDS_ARRAY_SIZE; i++) {
				//get element: depth;
				p1 = (float)(((uchar*)(pImg->imageData + pImg->widthStep*yy))[xx*3]);
				if ( p1 < 0.5)
					continue;
				p1 = 255-p1;
				
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
				fprintf( outfile, "%f\t", feat);				
			}
			fprintf(outfile, "\n");
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