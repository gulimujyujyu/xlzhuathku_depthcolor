%% train_step2_MoG.m
% For training the MoG classifier
% Step 2: generate a MoG Classifier from training data
% Xiaolong ZHU
% lucienzhu@gmail.com 
% The University of Hong Kong

close all
clear all
clc
%% includes
addPath('./lib/libsvm-3.1/matlab')
%% Globals
g_dirr = 'E:/DATA/[CDC4CV11]/RealTest/2011_28_06_21_14_10_943/';
g_version = '0.1';
g_fileName_output = ['svm_' g_version '.classifier'];
g_m = 3;
g_numOfClass = 7;
g_color = {
    '.r','*r';
    '.k','*k';
    '.b','*b';
    '.g','*g';
    '.y','*y';
    '.c','*c';
    '.m','*m';    
    };

%% Training
trainData = [];
for label = 1:g_numOfClass
    %close the file
    fileName_input = ['train_label_' num2str(label) '.txt'];
    fin = fopen([g_dirr fileName_input]);
    if fin < 0
        printf('Open File Failed: %s', fileName_input);
        return;
    end
    %read data
    data = fscanf(fin, '%d %d %d %d', [4 inf]);
    trainData = [trainData; data'];
    %close the file
    fclose(fin);
end
svmModel = svmtrain(trainData(:,4), trainData(:,1:3),'-c 5 -g 0.07 -b 1');

%test
[predict_label, accuracy, prob_estimates] = svmpredict(trainData(:,4), trainData(:,1:3), svmModel, '-b 1');

%% draw
figure(1)
hold on
[X Y] = size(trainData);
for ii = 1:X
    result = g_color{predict_label(ii)+1,1};
    plot3(trainData(ii,1),trainData(ii,2),trainData(ii,3),result);
end

%% Write to files
fout = fopen([g_dirr g_fileName_output], 'w');
save( [g_dirr g_fileName_output], 'svmModel', 'g_numOfClass', 'g_m');