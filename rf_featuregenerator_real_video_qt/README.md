	*************************************
	Video to Images for Real Experiment
	Xiaolong ZHU@HKU
	lucienzhu@gmail.com
	*************************************

#1. Prerequisites

##1.1 Dependencies

*. OpenCV 2.1 for VS2008
*. Qt 4.7 for VS2008

1. [OpenCV](http://opencv.willowgarage.com/wiki/VisualC%2B%2B_VS2008)

#2. Usage

Generate images from videos.

##2.1 Video format

Video format is two images in a row, left is color and right is depth image.
The two images are registered after calibration.

##2.2 Step

1. Specify the path containing the videos by passing the arguments.
2. The program will create a folder when it is running.

#3. Empirical Notes

#4. Data

##4.1 output
	{timeStamp}/
		{nowStamp}_{lb_ub}image.png. Color Image.
		{nowStamp}_{lb_ub}depth.png. Depth Image.

	{timeStamp} := {yyyy_dd_MM_hh_mm_ss_zzz}
	{nowStamp} := {yyyy_dd_MM_hh_mm_ss_zzz}
	{lb_ub} := {nearPlaneKinect_farPlaneKinect}