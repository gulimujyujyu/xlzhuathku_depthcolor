	*************************************
	Image Feature Generator for Real Experiment.
	Xiaolong ZHU@HKU
	lucienzhu@gmail.com
	*************************************

#1. Prerequisites

##1.1 Dependencies

*. OpenCV 2.1 for VS2008
*. QT4.7 for VS2008

1. [OpenCV](http://opencv.willowgarage.com/wiki/VisualC%2B%2B_VS2008)

#2. Usage

Generate Training Set for Training a Random Forest.
This part is without GPU acceleration.

##2.1 Step

1. Change the height and width of depth map in "main.cpp"
2. Change the number START_FILE_NUM and END_FILE_NUM for images in "main.cpp"
3. Change the containing folder path in "main.cpp"
4. Change the lon and lat in "main.cpp"
5. Change the label for each part in "featuregenerator.cpp"
6. Change the macros in "featuregenerator.h"
7. Run the program.

#3. Empirical Notes

#4. Data

