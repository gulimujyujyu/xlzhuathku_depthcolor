#pragma once

#ifndef IMAGEGENERATOR_H
#define IMAGEGENERATOR_H

#define SEEDS_ARRAY_SIZE 2000
class FeatureGenerator
{
public:
	FeatureGenerator(void);
	~FeatureGenerator(void);
	bool read( const char * filename);
	void setParameter( int w, int h, int rw, int rh);
	void setSeeds( int a[SEEDS_ARRAY_SIZE], int b[SEEDS_ARRAY_SIZE]);
	void generateFeatures();
	bool write( const char* filename, int flag);

private: 
	//TODO
	int width;
	int height;
	int rectWidth;
	int rectHeight;
	int seedsX[SEEDS_ARRAY_SIZE];
	int seedsY[SEEDS_ARRAY_SIZE];
};
#endif
