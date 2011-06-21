%% playground.m
% for doodle-like testing
% Xiaolong ZHU
% lucienzhu@gmail.com 
% The University of Hong Kong

%% Globals
g_dirr = 'E:/DATA/[CDC4CV11]/ForRealData/222/';
g_version = '0.1';
g_fileName_output = ['mog_' g_version '.classifier'];
label = 1;

% test
fileName_input = ['train_label_' num2str(label) '.txt'];
fin = fopen([g_dirr fileName_input]);
if fin < 0
    printf('Open File Failed: %s', fileName_input);
    return;
end

%read data
data = fscanf(fin, '%d %d %d %d', [4 inf]);

ma = max(data');
mi = min(data');

aa = length(mi);

for i=1:aa
    mu = min(i) + (max(i)-min(i))*rand();
end

%close
fclose(fin);

%% lalala
