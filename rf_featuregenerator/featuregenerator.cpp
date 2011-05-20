#include "featuregenerator.h"

FeatureGenerator::FeatureGenerator(void)
{
}

FeatureGenerator::~FeatureGenerator(void)
{
}

bool FeatureGenerator::read(const char * filename)
{
	//TODO
	return true;
}

bool FeatureGenerator::write(const char* filename, int flag = 0)
{
	//TODO
	return false;
}

void FeatureGenerator::generateFeatures()
{

}

void FeatureGenerator::setParameter(int w, int h, int rw, int rh)
{
	this->width = w;
	this->height = h;
	this->rectWidth = rw;
	this->rectHeight = rh;
}

void FeatureGenerator::setSeeds(int a[SEEDS_ARRAY_SIZE], int b[SEEDS_ARRAY_SIZE])
{
	int i;
	for( i=0; i<SEEDS_ARRAY_SIZE; i++) {
		this->seedsX[i] = a[i];
		this->seedsY[i] = b[i];
	}
}