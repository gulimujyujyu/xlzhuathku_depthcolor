    ***********************************
    Random Forest Training Set Generation for Real Data
    Xiaolong ZHU@HKU
    lucienzhu@gmail.com
    ***********************************

#1. Prerequisites

##1.1 Dependencies

*. Matlab 2009a or Higher
*. Libsvm 3.1

#2. Usage

For the script name

##2.1 Training

For training a color classifier,
1. Get mask manually using image editing, like photoshop
    1.1. follow the naming convention
        image: blabla.png
        mask for label 1: blabla_1.png
        mask for label 2: blabla_2.png
        ...

2. specify the training image in 'train_step1_generate.m', like blabla.png
    2.1 it will save a several 'label_x.txt' in the folder you specified.

3. traing the classifier using 'train_step2_mog.m' OR 'train_step2_svm.m'
    3.1 it will save a classifier '*.classifer' with some global variables in the folder you specified.
    3.2 mog is better because they are a set of detectors;
    3.3 svm is not so good as the negative example is not so easy to archieve, so far it is a multi-class classifier, rather than a set of 0-1 detector.

##2.2 Generation
1. Put all paired data in the certain folder.
2. Run 'generation_step1.m' to get the training data.

#3. Empirical Notes

#4. Data

