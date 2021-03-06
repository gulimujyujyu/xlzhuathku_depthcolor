	*********************************
	Train A Random Forest in CPU
	Xiaolong ZHU@HKU
	lucienzhu@gmail.com
	*********************************

#1. Prerequisites

##1.1 Dependencies

*. OpenCV 2.1 for VS2008

1. [OpenCV for VS2009](http://opencv.willowgarage.com/wiki/VisualC%2B%2B_VS2008)

#2. Usage

Train a tree or a RF for prediction.

##2.1 Step

1. Specify the macros in "item.h", "id3tree.h"
2. Specify number of training samples in "main.cpp"
3. Specify three paths in "main.cpp"
4. Run the program.

#3. Empirical Notes

Macros like:
	//in "item.h"
	#define SEEDS_ARRAY_SIZE 400
	#define FEATURE_DIM (SEEDS_ARRAY_SIZE/2)
	#define CLASS_NUM 7
	//in "id3tree.h"
	#define ATTRIBUTES_PER_ROUND 10
	#define ATTRIBUTES_NUM_OF_RETRY 10
	#define MAX_ATTRIBUTE_VALUE 999999
	#define MIN_ATTRIBUTE_VALUE -999999
	#define HISTO_BINS 8
	#define ZERO_ENTROPY 1e-9
	#define MAX_GAIN_VALUE 999999
	must be changed w.r.t. the certain dataset.

*. Hopefully, these code can be optimized and better organized.