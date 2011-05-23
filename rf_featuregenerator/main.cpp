#include <iostream>
#include <string>
#include "featuregenerator.h"
#include "time.h"
using namespace std;

int offx[SEEDS_ARRAY_SIZE];
int offy[SEEDS_ARRAY_SIZE];

void generateSeeds()
{
	for ( int i=0; i < SEEDS_ARRAY_SIZE; i++) {
		offx[i] = rand();
		offy[i] = rand();
	}
}

int main()
{
	string dirr = "F:\\xlzhu\\DATAs\\[CDC4CV]HandTracking\\000\\";
	string inFilename = dirr + "0_0_2011_19_05_15_13_42_938depth.png";
	string labelFilename = dirr + "0_0_2011_19_05_15_13_43_037color.png";;
	string outFilename = dirr + "000000.txt";
	string outLabelFilename = dirr + "000000.label";
	int w = 512;
	int h = 512;
	int rw = 64;
	int rh = 64;


	srand(time(NULL));
	generateSeeds();

	FeatureGenerator a;
	a.setSeeds(offx, offy);
	a.setParameter(w,h,rw,rh);
	a.createHash();

	if (!(a.read(inFilename.c_str())))
	{
		printf("Error occured in reading %s", inFilename.c_str());
		return -1;
	}
	if (!(a.readLabel(labelFilename.c_str())))
	{
		printf("Error occured in reading %s", labelFilename.c_str());
		return -1;
	}
	if (!(a.setOutputFilename(outFilename.c_str(), 0)))
	{
		printf("Error occurred in writing to %s", outFilename.c_str());
	}
	if (!(a.setOutputFilenameLabel(outLabelFilename.c_str(), 0)))
	{
		printf("Error occurred in writing to %s", outLabelFilename.c_str());
	}
	a.generateFeatures();
	a.generateLabels();
	
	
	return 0;
}