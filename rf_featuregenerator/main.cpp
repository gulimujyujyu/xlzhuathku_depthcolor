#include <iostream>
#include <string>
//#include <regex>
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
	string dirr = "E:\\DATA\\[CDC4CV11]\\ForPrediction\\";
	string inFilename = dirr + "000000_color.png";
	string labelFilename = dirr + "000000_label.png";;
	string outFilename = dirr + "000000.txt";
	string outParamFilename = dirr + "000000.param";
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
	if (!(a.setOutputFilename(outFilename.c_str(),outParamFilename.c_str(), 0)))
	{
		printf("Error occurred in writing to %s, %s", outFilename.c_str(),outParamFilename.c_str());
	}
	if (!(a.setOutputFilenameLabel(outLabelFilename.c_str(), 0)))
	{
		printf("Error occurred in writing to %s", outLabelFilename.c_str());
	}
	a.generateFeatures();
	a.generateLabels();
	
	
	return 0;
}