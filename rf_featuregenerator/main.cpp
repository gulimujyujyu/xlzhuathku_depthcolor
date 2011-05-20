#include <iostream>
#include "featuregenerator.h"

int main()
{
	char inFilename[256] = "";
	char outFilename[256] = "";
	int w;
	int h;
	int rw;
	int rh;
	int offx[SEEDS_ARRAY_SIZE];
	int offy[SEEDS_ARRAY_SIZE];

	FeatureGenerator a;
	a.setSeeds(offx, offy);
	a.setParameter(w,h,rw,rh);

	if (!(a.read(inFilename)))
	{
		printf("Error occured in reading %s", inFilename);
		return -1;
	}
	a.generateFeatures();
	if (!(a.write(outFilename, 0)))
	{
		printf("Error occurred in writing to %s", outFilename);
	}
	
	return 0;
}