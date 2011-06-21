function [prob decision] = mog_predict( item, gmm, m, nClass)
%MOG_PREDICT Summary of this function goes here
%   Detailed explanation goes here
prob = zeros(nClass, 1);
for ii = 1:nClass
    prob(ii) = pdf(gmm{ii}, item);
end
prob = prob./sum(prob);
[p decision] = max(prob);
end

