%% generate_step1.m
% Feature Generation 
% Xiaolong ZHU
% lucienzhu@gmail.com 
% The University of Hong Kong
close all
clear all
clc;
%% includes
addPath('./lib/bfilter2/BilateralFiltering');

%% globals
% g_dirr = 'C:/Users/xiaolongzhu/Research/PROJECTs/[CDC4CV]HandTracking/DATA/ForRealData/333/train/' %xlzhumac
g_dirr = 'E:/DATA/[CDC4CV11]/RealTest/2011_28_06_21_14_10_943/'; %xlzhulab
% 2011_22_06_07_20_19_730_978_677depth
g_pattern_prefix = '\d{4}_\d{2}_\d{2}_\d{2}_\d{2}_\d{2}_\d{3}_\d{3}_\d{3}';
g_pattern_postfix_depth = 'depth.png';
g_pattern_postfix_color = 'image.png';
g_version = '0.1';
g_classifierName = ['mog_' g_version '.classifier'];
g_refine_flag = 0; %0: conservative; 1: radical
g_refine_neigh = [5 5];
g_refine_thres = 16;
g_startNum = 0;
colorMapping = [
    255 0 0;
    255 0 255;
    0 0 255;
    0 255 0;
    0 255 255;
    255 255 255;
    255 255 0;
    ];

load([g_dirr g_classifierName],'-mat');
%% Step 1:
% list the files in the folder
flist = dir(g_dirr);
flist_length = length(flist);

strList = [];

% find pairs
for ii = 1:flist_length
    res = regexp(flist(ii).name, g_pattern_prefix, 'match');
    res_depth = regexp(flist(ii).name, [g_pattern_prefix g_pattern_postfix_depth], 'match');
    if length(res) > 0 && length(res_depth) > 0
        fn_depth = [g_dirr res{1} g_pattern_postfix_depth];
        fn_color = [g_dirr res{1} g_pattern_postfix_color];
        if exist(fn_depth) && exist(fn_color)
            strList = [strList; fn_depth; fn_color];
        end
    end
end

%% Step 2:
% for each pair generate feature
numOfFiles = size(strList,1)/2;

for ii = 1:10:numOfFiles
    %% step 2.1: pre-processing
    % bilateral filter must in [0,1]
    im_co = double(imread(strList(ii*2,:)))/255;
    im_de = double(imread(strList(ii*2-1,:)))/255;
    
    % bilateral filter
    % Set bilateral filter parameters.
    bf_w     = 7;       % bilateral filter half-width
    bf_sigma = [10 0.2]; % bilateral filter standard deviations
    im_bf = bfilter2(im_co,bf_w,bf_sigma);
    
    % set mask
    im_masked = im_bf;
    [X Y nChannel] = size(im_masked);
    for xx = 1:X
        for yy = 1:Y
            item1 = squeeze(im_co(xx,yy,:)).*255;
            item2 = squeeze(im_de(xx,yy,:)).*255;
            if( norm(item1) < 40 || norm(item2) < 2)
                im_masked(xx,yy,:) = 0;
            end
        end
    end
    
    figure(1);
    subplot(2,2,1);
    imshow(im_co);
    subplot(2,2,2);
    imshow(im_de);
    subplot(2,2,3);
    imshow(im_masked);
    subplot(2,2,4);
    imshow(im_bf);
    
    %% STEP 2.2: classify the pixels
    [X Y nChannel] = size(im_masked);
    im_res = im_masked;
    im_lbl = zeros(X,Y);
    for xx = 1:X
        for yy = 1:Y
            item = squeeze(im_masked(xx,yy,:));
            item = item'*255;
            if norm(item) <= 1
                im_res(xx,yy,:) = 0;
            else
                [prob class] = mog_predict(item, gmm, g_numOfClass);
                %[prob class] = svm_predict(item, svmModel, g_m, g_numOfClass);
                if class == -1 || class == 7
                    im_res(xx,yy,:) = 0;
                else
                    im_res(xx,yy,1) = colorMapping(class,1);
                    im_res(xx,yy,2) = colorMapping(class,2);
                    im_res(xx,yy,3) = colorMapping(class,3);
                    im_lbl(xx,yy) = class;
                end
            end
        end
    end
    figure(2)
    subplot(2,2,1);
    imshow(im_co);
    subplot(2,2,2);
    imshow(im_de);
    subplot(2,2,3);
    imshow(im_masked);
    subplot(2,2,4);
    imshow(im_res);
    
    %% step 2.3: post-processing
    im_lbl = refine_labels(im_lbl, g_refine_neigh, g_numOfClass, g_refine_thres, g_refine_flag);
    for xx = 1:X
        for yy = 1:Y
            class = im_lbl(xx,yy);
            if class == 0 || class == 7 || class == -1
                im_res(xx,yy,:) = 0;
            else
                im_res(xx,yy,1) = colorMapping(class,1);
                im_res(xx,yy,2) = colorMapping(class,2);
                im_res(xx,yy,3) = colorMapping(class,3);
            end
        end
    end
    figure(3)
    subplot(2,2,1);
    imshow(im_co);
    subplot(2,2,2);
    imshow(im_masked);
    subplot(2,2,3);
    imshow(im_res);
    subplot(2,2,4);
    imshow(im_lbl/g_numOfClass);
    
    imwrite(im_de, [g_dirr num2str(ii+g_startNum-1) 'depth.png']);
    imwrite(im_res, [g_dirr num2str(ii+g_startNum-1) 'color.png']);
    imwrite(im_co, [g_dirr num2str(ii+g_startNum-1) 'image.png']);
end
