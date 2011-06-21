function [ prob decision ] = svm_predict( item, svm, m, nClass )
%SVM_PREDICT Summary of this function goes here
%   Detailed explanation goes here
[decision, accuracy, prob] = svmpredict(1, item, svm, '-b 1');
decision = decision+1;
end

