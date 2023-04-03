function [ ref_descriptors ref_locations ] = self_feature_selection( dataFileName, pointNum )
% 參考的 SIFT 特徵由大量自身挑選留下較少數量具有重要份量的特徵點
% self_feature_selection( 讀取訓練的 dateset, 篩選保留數量 )

[im, des, loc] = sift( dataFileName );

ref_descriptors = des;
ref_locations = loc;

if size(des,1) > pointNum
    
    % self dot product match
    %
    distRatio = 0.6;   
    match = struct;
    match_count = zeros(size(des,1),1);

    % For each descriptor in the first image, select its match to second image.
    des_t = des';                          % Precompute matrix transpose
    for i = 1: size(des,1)
       dotprods = des(i,:) * des_t;        % Computes vector of dot products
       [vals,indx] = sort(acos(dotprods));  % Take inverse cosine and sort results

       % Check if nearest neighbor has angle less than distRatio times 2nd.
       %
       % 一個特徵點同時尋找多個匹配
       j = find( (vals(1:end-1) < distRatio * vals(2:end))==0,1,'first');
       if j > 1
           match(i).corre = indx(1:j-1);
           match_count(i) = j-1;
       else
           match(i).corre = 0;
       end
    end

    [vals,indx] = sort(match_count);
    remains = indx(1:300);
   
    ref_descriptors = des(remains,:);
    ref_locations = loc(remains,:);

end

%% 使用 k-means 方法篩選

% k-means
%{
k = 300;
[IDX,C] = kmeans(des,k);
reduced_des_idx = zeros(k,1); 

for i = 1:k
    cluster_index = find(IDX==i);
    clusterSize = size(cluster_index,1);
    
    dist_min = realmax('single');
        
    for j = 1:clusterSize 
        distance = norm( des(cluster_index(j),:) - C(i,:) );
        if distance < dist_min
            dist_min = distance;
            most_near_centroid = cluster_index(j);
        end        
    end
    
    reduced_des_idx(i) = most_near_centroid;
    %plot( loc(most_near_centroid,2), loc(most_near_centroid,1), 'r+' );
end

remains = reduced_des_idx;

%fprintf('demo:Found %d matches.\n', num);

%}

%%

% 用累積的歐式距離篩選累積距離較小者
% E-dist error accumulation
%{
acc_Error = zeros(size(des,1),1);
for i = 1: size(des,1)
    error = 0;
    
    for j = 1: size(des2,1)
        error = error + norm( des(i,:)-des2(j,:) );
    end
    
    acc_Error(i) = error;
    
    [vals,indx] = sort(acc_Error);
    
end

remains = indx(1:300);

%}


%%

% 計算一個特徵點對其他特徵點小於設定的歐式距離的匹配個數，取數量最多的前N個點
% amount of E-dist similarity
%{
number_of_match = zeros(size(des,1),1);

for i = 1: size(des,1)
    
    for j = 1: size(des2,1)
        if norm( des(i,:)-des2(j,:) ) < 0.3
            number_of_match(i) = number_of_match(i) + 1;
        end
    end
     
    [vals,indx] = sort( number_of_match );
    
end

remains = indx(1:300);

%}

end

