function [ im_lbl ] = refine_labels( im_lbl, neighbor_size, numOfLabel, thres, flag)
%UNTITLED2 Summary of this function goes here
%   im_lbl: uint8 gray-scale array
if flag == 0
    % TODO: try the conservative way
    [X Y] = size(im_lbl);
    histo = zeros( X,Y, numOfLabel);
    % voting
    left = floor(neighbor_size(1)/2);
    right = floor((neighbor_size(1)-.5)/2);
    up = floor(neighbor_size(2)/2);
    down = floor((neighbor_size(2)-0.5)/2);
    for xx = left+1:X-right
        for yy = up+1:Y-down
            for ii = 1:numOfLabel
                histo(xx,yy,ii) = sum(sum(im_lbl(xx-left:xx+right,yy-up:yy+down)==ii));
            end
        end
    end
    % harvesting
    [im_val im_lbl] = max(histo, [],3);
    im_lbl( im_val<thres) = 0;
elseif flag == 1
    % this is the radical way
    im_lbl = medfilt2(im_lbl, neighbor_size);
else
%     im_lbl = im_lbl;
end

end

