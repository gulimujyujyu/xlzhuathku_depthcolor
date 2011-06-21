%% train_step1_generate.m
% For training the MoG classifier
% Step 1: generate the training data
% Xiaolong ZHU
% lucienzhu@gmail.com 
% The University of Hong Kong

%% Globals
g_dirr = 'E:/DATA/[CDC4CV11]/ForRealData/222/';
g_imgName_color = '2011_13_06_11_24_51_565_839_671image.png';
g_label = 7;
g_imgName_mask = ['2011_13_06_11_24_51_565_839_671mask_' num2str(g_label) '.png'];
g_fileName_output = ['train_label_' num2str(g_label) '.txt'];

%% read images
im_co = imread([g_dirr g_imgName_color]);
im_ma = imread([g_dirr g_imgName_mask]);

im_masked = im_co;
im_masked(im_ma < 128) = 0;

figure(1);
subplot(1,2,1);
imshow(im_co);
subplot(1,2,2);
imshow(im_masked);

%% output g_labels
fout = fopen([g_dirr g_fileName_output],'a');

if fout < 0
    printf('Open File Failed: %s', g_fileName_output);
    return;
end
[X Y Z] = size(im_co);
for xx = 1:X
    for yy = 1:Y
        if im_masked(xx,yy,1) > 0 && ...
           im_masked(xx,yy,2) > 0 && ...
           im_masked(xx,yy,3) > 0 
            fprintf( fout, '%d %d %d %d\n', im_masked(xx,yy,1), ...
                im_masked(xx,yy,2), im_masked(xx,yy,3), g_label-1);
        end
    end
end

fclose(fout);