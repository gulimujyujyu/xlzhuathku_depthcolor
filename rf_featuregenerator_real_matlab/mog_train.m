function [ gmm] = mog_train( data, m )
%Train a GMM Model given the training data
%   data = [ attri_1, ...., attri_n ;label]
%   m: number of components
%   model: mu + Sigma + p

lb = data(:,1:end-1);
dt = data(:,end);

[itemNum itemDim] = size(lb);

% random choose m mu with identity covariance matrix
ma = max(lb);
mi = min(lb);

mu = zeros(m,itemDim);
sigma = zeros(itemDim, itemDim, m);
for ii = 1:m
    mu(ii,:) = zeros(1,itemDim);
    sigma(:,:,ii) = eye(itemDim)*255;
    for jj = 1:itemDim
        mu(ii,jj) = mi(jj)+(ma(jj)-mi(jj))*rand();
    end
end
p = ones(1,m)/m;

%begin iterations
epsilon = 999;
while(epsilon > 1e-3)
    %scan through the whole set
    mu_before = mu;
    %E-Step:
    weiMat = zeros(itemNum, m);
    gmm = gmdistribution(mu, sigma, p);
    for ii = 1:m
        for jj = 1:itemNum
            weiMat(jj,ii) = mvnpdf(lb(jj,:),mu(ii,:),sigma(:,:,ii))*p(ii);
        end
    end
    weiMat_norm = sum(weiMat, 2);
    weiMat = weiMat ./ (repmat(weiMat_norm,1,m));
    %M-Step:
    p = sum(weiMat,1);
    for ii = 1:m
        mu(ii,:) = sum(lb.*repmat(weiMat(:,ii),1,itemDim),1)./p(ii);
        tmp = repmat(mu(ii,:),itemNum,1);
        tmp = lb-tmp;
        sigma(:,:,ii) = tmp'*(repmat(weiMat(:,ii),1,itemDim).*tmp)./p(ii);
    end
    p = p/itemNum;
    %calculate the epsilon
    mu_before = (mu - mu_before);
    epsilon = 0;
    for ii=1:m
        epsilon = norm(mu_before(ii,:)) + epsilon;
    end
end

end

