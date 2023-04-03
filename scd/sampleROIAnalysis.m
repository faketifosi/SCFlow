function [ROI_property] = sampleROIAnalysis( im )
% 分析給定的 ROI 特徵 ( 連通元件大小與高寬比，ROI 高寬比，水平區間比值序列特徵，垂直區間比值序列特徵 )

% binarization
im = rgb2gray(im);
level = graythresh(im);
BW = im2bw(im,level);

% truncate removal
truncate = true;
while(truncate)
    truncate = false;
    if sum( BW(1,:) == 0 ) == 0
        BW(1,:) = [];
        truncate = true;
    end
    if sum( BW(end,:) == 0 ) == 0
        BW(end,:) = [];
        truncate = true;
    end
    if sum( BW(:,1) == 0 ) == 0
        BW(:,1) = [];
        truncate = true;
    end
    if sum( BW(:,end) == 0 ) == 0
        BW(:,end) = [];
        truncate = true;
    end
end


ROI_property = struct;

ROI_property.representation_of_components = [];
ROI_property.aspect_ratio = size(BW,2) / size(BW,1);
ROI_property.ROI_to_CCs_ratio = [];
ROI_property.horizontal_align_rule = 0;
ROI_property.vertical_align_rule = 0;

BW = imresize(BW,[100 ROI_property.aspect_ratio*100]);

% ROI的水平與垂直投影
ROI_property.hor_hist = zeros( size(BW,1),1 );
for i = 1:size(BW,1)
    ROI_property.hor_hist(i) = sum( BW(i,:) == 0 );
end

ROI_property.ver_hist = zeros( 1,size(BW,2),1 );
for i = 1:size(BW,2)
    ROI_property.ver_hist(i) = sum( BW(:,i) == 0 );
end

% 計算 component 水平和垂直排列的規則
% 由水平垂直投影取大略分佈(黑白相間比值的sequence)
% 參考 ROI_validate
atRegion = false;
interval_area_seq = []; interval = 0;
ROI_property.ver_hist = ROI_property.ver_hist( find(ROI_property.ver_hist>2, 1, 'first'):find(ROI_property.ver_hist>2, 1, 'last') );
for i = 1:size(ROI_property.ver_hist,2)
    if ROI_property.ver_hist(i) > 2 && ~atRegion 
        if interval ~= 0
            interval_area_seq = [interval_area_seq interval];
            interval = 0;
        end
        atRegion = true;
        interval = interval + 1; 
    elseif ROI_property.ver_hist(i) > 2 && atRegion
        interval = interval + 1; 
    elseif ~(ROI_property.ver_hist(i) > 2) && ~atRegion
        interval = interval + 1; 
    elseif ~(ROI_property.ver_hist(i) > 2) &&  atRegion
        if interval ~= 0
            interval_area_seq = [interval_area_seq interval];
            interval = 0;
        end
        atRegion = false;
        interval = interval + 1; 
    end
    
    if i == size(ROI_property.ver_hist,2)
        interval_area_seq = [interval_area_seq interval];
    end       
end

if size(interval_area_seq,2) > 1
    ROI_property.horizontal_align_rule = interval_area_seq(1:end-1) ./ interval_area_seq(2:end);
end

atRegion = false;
interval_area_seq = []; interval = 0;
ROI_property.hor_hist = ROI_property.hor_hist( find(ROI_property.hor_hist>2, 1, 'first'):find(ROI_property.hor_hist>2, 1, 'last') );
for i = 1:size(ROI_property.hor_hist,1)
    if ROI_property.hor_hist(i) > 2 && ~atRegion 
        if interval ~= 0
            interval_area_seq = [interval_area_seq interval];
            interval = 0;
        end
        atRegion = true;
        interval = interval + 1; 
    elseif ROI_property.hor_hist(i) > 2 && atRegion
        interval = interval + 1; 
    elseif ~(ROI_property.hor_hist(i) > 2) && ~atRegion
        interval = interval + 1; 
    elseif ~(ROI_property.hor_hist(i) > 2) &&  atRegion
        if interval ~= 0
            interval_area_seq = [interval_area_seq interval];
            interval = 0;
        end
        atRegion = false;
        interval = interval + 1; 
    end
    
    if i == size(ROI_property.hor_hist,1)
        interval_area_seq = [interval_area_seq interval];
    end       
end

if size(interval_area_seq,2) > 1
    ROI_property.vertical_align_rule = interval_area_seq(1:end-1) ./ interval_area_seq(2:end);
end

BW = 1 - BW;

CCs = bwconncomp(BW,8);
CCp = regionprops(CCs);

if size(CCp,1) > 1
    for i = size(CCp,1):-1:1
        if CCp(i).Area < 10 
            CCp(i) = [];
            CCs.PixelIdxList(i) = [];
        end
    end
end

for i = 1:size(CCp,1)
    ROI_property.representation_of_components(i,1).position = [(CCp(i).BoundingBox(1)+CCp(i).BoundingBox(3)/2) / size(im,2) (CCp(i).BoundingBox(2)+CCp(i).BoundingBox(4)/2) / size(im,1)];
    ROI_property.representation_of_components(i,1).size = [CCp(i).BoundingBox(3) / size(im,2) CCp(i).BoundingBox(4) / size(im,1)];
end

CC_tempSeq = zeros(size(CCp,1),1);

for i = 1:size(CCp,1)
    CC_tempSeq(i) = [CCp(i).BoundingBox(3) * CCp(i).BoundingBox(4)];
end

[CC_sortByArea index] = sort(CC_tempSeq);
medianAreaCC = index( floor(size(index,1)/2) + 1 );


ROI_property.ROI_to_CCs_ratio.widthRatio = size(im,2) / CCp(medianAreaCC).BoundingBox(3);
ROI_property.ROI_to_CCs_ratio.heightRatio = size(im,1) / CCp(medianAreaCC).BoundingBox(4);


BW = 1-BW;
figure;
imshow(BW);
figure;
bar(ROI_property.ver_hist);

end

