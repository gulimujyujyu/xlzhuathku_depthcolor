
%% includes
addPath('./lib/bfilter2/BilateralFiltering');

%% Globals
g_dirr = 'E:/DATA/[CDC4CV11]/ForRealData/333/';
g_imgName_color = '2011_22_06_07_20_19_730_978_677image.png';
g_imgName_depth = '2011_22_06_07_20_19_730_978_677depth.png';
g_imgName_bf = '2011_22_06_07_20_19_730_978_677bf.png';
g_version = '0.1';
g_classifierName = ['svm_' g_version '.classifier'];
colorMapping = [
    255 0 0;
    255 0 255;
    0 0 255;
    0 255 0;
    0 255 255;
    255 255 255;
    255 255 0;
    ];

%% STEP 1: process image
% bilateral filter must in [0,1]
im_co = double(imread([g_dirr g_imgName_color]))/255;
im_de = double(imread([g_dirr g_imgName_depth]))/255;

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