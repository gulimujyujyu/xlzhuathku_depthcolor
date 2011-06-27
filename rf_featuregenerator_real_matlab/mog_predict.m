function [prob decision] = mog_predict( item, gmm, nClass)
%MOG_PREDICT Summary of this function goes here
%   Detailed explanation goes here
%% globals
THRESHOLD_PROB = 0.95;
%% codes
prob = zeros(nClass, 1);
for ii = 1:nClass
    prob(ii) = pdf(gmm{ii}, item/255);
end
prob = prob./sum(prob);
[p decision] = max(prob);

if p < THRESHOLD_PROB
    decision = -1;
end
end

