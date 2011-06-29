%% train_step1_generate.m
% For training the MoG classifier
% Step 1: generate the training data
% Xiaolong ZHU
% lucienzhu@gmail.com 
% The University of Hong Kong

%% includes
addPath('./lib/bfilter2/BilateralFiltering');

%% Globals
g_dirr = 'E:/DATA/[CDC4CV11]/ForRealData/444/';
g_imgName_color = '2011_22_06_07_20_19_730_978_677image.png';
g_label = 6;
g_imgName_mask = ['2011_22_06_07_20_19_730_978_677mask_' num2str(g_label) '.png'];
g_fileName_output = ['train_label_' num2str(g_label) '.txt'];
g_numOfSamples = 1000;

%% read images
im_co = double(imread([g_dirr g_imgName_color]))/255;
im_ma = imread([g_dirr g_imgName_mask]);

% bilateral filter
% Set bilateral filter parameters.
bf_w     = 7;       % bilateral filter half-width
bf_sigma = [10 0.2]; % bilateral filter standard deviations
im_bf = bfilter2(im_co,bf_w,bf_sigma);
im_bf = uint8(im_bf*255);

im_masked = im_bf;
im_masked(im_ma < 128) = 0;

figure(1);
subplot(1,2,1);
imshow(im_bf);
subplot(1,2,2);
imshow(im_masked);

%% output g_labels
fout = fopen([g_dirr g_fileName_output],'a');

if fout < 0
    printf('Open File Failed: %s', g_fileName_output);
    return;
end
[X Y Z] = size(im_co);
writtenData = [];
for xx = 1:X
    for yy = 1:Y
        if im_masked(xx,yy,1) > 0 && ...
           im_masked(xx,yy,2) > 0 && ...
           im_masked(xx,yy,3) > 0 
            writtenData = [writtenData; im_masked(xx,yy,1), ...
                im_masked(xx,yy,2), im_masked(xx,yy,3), g_label-1];
        end
    end
end

[X Y] = size(writtenData);

if X > g_numOfSamples
    step = ceil(X/g_numOfSamples);
    writtenData = writtenData(1:step:end,:);
end

[X Y] = size(writtenData);
for xx = 1:X
    fprintf( fout, '%d %d %d %d\n', writtenData(xx,1), ...
        writtenData(xx,2), writtenData(xx,3), writtenData(xx,4));
end

fclose(fout);