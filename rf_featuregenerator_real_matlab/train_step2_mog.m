%% train_step2_MoG.m
% For training the MoG classifier
% Step 2: generate a MoG Classifier from training data
% Xiaolong ZHU
% lucienzhu@gmail.com 
% The University of Hong Kong

close all
clear all
clc

%% Globals
% g_dirr = 'C:/Users/xiaolongzhu/Research/PROJECTs/[CDC4CV]HandTracking/DATA/ForRealData/333/' %xlzhumac
g_dirr = 'E:/DATA/[CDC4CV11]/RealTest/2011_28_06_21_14_10_943/'; %xlzhulab
g_version = '0.1';
g_fileName_output = ['mog_' g_version '.classifier'];
g_m = 3;
g_numOfClass = 7;
g_color = {
    '.r','*g';
    '.k','*w';
    '.b','*y';
    '.g','*r';
    '.y','*b';
    '.c','*m';
    '.m','*c';    
    };

%% Training
gmm = cell(g_numOfClass,1);
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
    data = data';
    %fit distribution
    gmm{label} = mog_train(data, g_m);
    %plot
    figure(1)
    hold on
    scatter3(data(:,1),data(:,2),data(:,3),g_color{label,1});
    plot3(gmm{label}.mu(:,1)*255,gmm{label}.mu(:,2)*255,gmm{label}.mu(:,3)*255,g_color{label,2});
    %close the file
    fclose(fin);
end

%% Write to files
fout = fopen([g_dirr g_fileName_output], 'w');
save( [g_dirr g_fileName_output], 'gmm', 'g_numOfClass', 'g_m');