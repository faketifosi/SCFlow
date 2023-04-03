function [] = SIFT_clustering_ROI( object_fileName )

global fig_handle;       % 全域 figure handle, 存檔之用
global ref_descriptors;  % 篩選後的特徵點
global ref_locations;    % 篩選後的特徵點座標
global file;             % 檔案編號, 存檔之用

% [參考影像, 特徵描述子, 特徵點座標]
[im, des, loc] = sift( object_fileName );

% SIFT 認定特徵點匹配的距離門檻值(相似度)
distRatio = 0.8; 

%
% 一個特徵點找多個對應點
match = struct;
match_count = zeros(size(ref_descriptors,1),1);

% For each descriptor in the first image, select its match to second image.
des_t = des';                          % Precompute matrix transpose
for i = 1: size(ref_descriptors,1)
   dotprods = ref_descriptors(i,:) * des_t;        % Computes vector of dot products
   [vals,indx] = sort(acos(dotprods));  % Take inverse cosine and sort results

   % Check if nearest neighbor has angle less than distRatio times 2nd.
   %
   j = find( (vals(1:end-1) < distRatio * vals(2:end)) == 0, 1, 'first');
   if j > 1
       match(i).corre = indx(1:j-1);
       match_count(i) = j-1;
   else
       match(i).corre = [];
   end
end
%}

% 一個特徵點只找一個對應點
%{ 
% For each descriptor in the first image, select its match to second image.
des_t = des';                          % Precompute matrix transpose
for i = 1 : size(ref_descriptors,1)
   dotprods = ref_descriptors(i,:) * des_t;        % Computes vector of dot products
   [vals,indx] = sort(acos(dotprods));  % Take inverse cosine and sort results

   % Check if nearest neighbor has angle less than distRatio times 2nd.
   if (vals(1) < distRatio * vals(2))
      match(i) = indx(1);
   else
      match(i) = 0;
   end
end
%}

%
% 多對應點採用
data = [];

for i = 1: size(ref_descriptors,1)
  if ~isempty(match(i).corre)
    for j = 1:size(match(i).corre,2)
        x = double(uint16(loc(match(i).corre(j),1)));
        y = double(uint16(loc(match(i).corre(j),2)));
        data = [data;[x y]];
    end
  end
end

num = size(data,1);
fprintf('Found %d matches.\n', num);
%}

%{
% 一個特徵點只有一個對應點採用
data = [];

for i = 1: size(ref_descriptors,1)
  if (match(i) > 0)
    %line([ref_locations(i,2) loc(match(i),2)+cols1], ...
    %    [ref_locations(i,1) loc(match(i),1)], 'Color', 'c');
    x = double(uint16(loc(match(i),1)));
    y = double(uint16(loc(match(i),2)));
    data = [data;[x y]];
  end
end

num = sum(match > 0);
fprintf('Found %d matches.\n', num);
%}

%畫出特徵點
fig_handle = figure(1); % show sift feature point
imshow(im, 'border', 'tight', 'initialmagnification', 'fit');
%set(gca,'Units','normalized','Position',[0 0 1 1]);  %# Modify axes size
set(fig_handle,'Position',[150 600 size(im,2) size(im,1)]);  %# Modify figure size

hold on;
plot(data(:,2), data(:,1), 'go', 'lineWidth', 2);
hold off;

%% Estimate candidate 
% 由 clustering 分析結果各個 cluster 移除離群點並依照分佈設定初步的候選區域

global xOrdered;    % 分群結果的全域變數，資料經分群後之順序 (在 optics_clustering 函式中操作 )

% 排除座標位置重複的特徵點
data = unique(data, 'rows');
% 特徵點座標輸入 
clusters = optics_clustering( data, im );

% 畫出 clusters
%
fig_handle = figure(2);  % candidate ROI
imshow(im, 'border', 'tight', 'initialmagnification', 'fit'); % impixelinfo;
set (gcf,'Position',[150,135,640,360]);

% color map
color =     [1 0 0;
             0 0 1;
             1 1 0;
             1 0 1;
             0 1 0;
             0 1 1;
             1 1 1;
             0 0 0 ];

hold on;

plot(data(:,2),data(:,1),'go','lineWidth',2);

candidate_ROI = [];

% 個別畫出 cluster 或 候選區域
for i = 1:numel(clusters)

    cluster = xOrdered(clusters(i).element(1):clusters(i).element(2),:);
  
    iterative = true; iter = 1;
    
    % 依順序求出兩兩之間歐式距離值
    distance_map = (cluster(1:end-1,2) - cluster(2:end,2)).^2 + (cluster(1:end-1,1) - cluster(2:end,1)).^2;
    % 計算方均根
    dist_rms_sum = sum( distance_map );    
    dist_rms_sum = ( dist_rms_sum / (size(cluster,1)-1) )^0.5;
    
    % 最多迭代三次移除與方均根相差過大的端短
    while iterative && iter < 3
        
        iterative = false;
                   
        if distance_map(1)^0.5 > dist_rms_sum
            cluster(1,:) = [];
            distance_map(1) = [];
            iterative = true;
        end

        if distance_map(end)^0.5 > dist_rms_sum
            cluster(end,:) = [];
            distance_map(end) = [];
            iterative = true;
        end
        
        iter = iter + 1;        
    end

    % 第一次的 line fitting
    [cfun gof] = fit(cluster(:,2), cluster(:,1),'poly1');
    plot( xOrdered([clusters(i).element(1):clusters(i).element(2)],2), xOrdered([clusters(i).element(1):clusters(i).element(2)],1), 'b+', 'linewidth', 2 );

    % plot( cfun, 'b' );    % 以藍色線顯示第一次 line fitting 結果
    axis off;
    % xlabel('');
    % ylabel('');

    % 計算所有點和第一次 fitting 的直線之距離的方均根
    point_dist = abs( (cfun.p1 * cluster(:,2) - cluster(:,1) + cfun.p2) / (cfun.p1^2 + 1)^0.5 );

    % 刪除距離太遠的離群點並執行第二次 line fitting
    if size(cluster,1) > 2
        points_inliers = cluster( find(point_dist <= 2*gof.rmse), : );
        [cfun gof] = fit(points_inliers(:,2), points_inliers(:,1), 'poly1');
    else
        points_inliers = cluster;
    end
 
    % 在影像上顯示第二次 fitting 結果與 剩下的點
    % points_inliers = cluster;
    plot( points_inliers(:,2),points_inliers(:,1),'yo', 'linewidth', 2 );
    % plot( cfun, 'g' );
    % xlabel(' ');
    % ylabel(' ');
    
    inliers_dist = (cfun.p1 * points_inliers(:,2) - points_inliers(:,1) + cfun.p2) / (cfun.p1^2 + 1)^0.5;
    
    % 最左，最右，最上，最下的點
    most_left_point   = points_inliers( find( points_inliers(:,2) == min(points_inliers(:,2)), 1 ), : );
    most_right_point  = points_inliers( find( points_inliers(:,2) == max(points_inliers(:,2)), 1 ), : );
    %{
    most_top_point    = points_inliers( find( inliers_dist == max(inliers_dist) ), : );
    most_bottom_point = points_inliers( find( inliers_dist == min(inliers_dist) ), : );
    %}    
    
    % 這裡由點形成框框不夠精準
    p1(2) = most_left_point(2);
    p1(1) = cfun.p1 * most_left_point(2) + cfun.p2;     % x 座標帶入方程式求 y
    p2(2) = most_right_point(2);      
    p2(1) = cfun.p1 * most_right_point(2) + cfun.p2;    % x 座標帶入方程式求 y
        
    upper_bound_dist =  max(inliers_dist);
    lower_bound_dist = -min(inliers_dist);
    left_axis_point =  point_poject_to_line( p1, p2, most_left_point );   % point of the most left point project to line
    right_axis_point = point_poject_to_line( p1, p2, most_right_point );  % point of the most right point project to line
    dist_bet_points = norm(right_axis_point - left_axis_point);           % distance between left_axis_point and right_axis_point
          
    % legend({'ori','before','cur','after'});
    legend off;
    %{    
    plot(left_axis_point(2), left_axis_point(1), 'wo', 'lineWidth',2);
    plot(right_axis_point(2), right_axis_point(1), 'wo', 'lineWidth',2);
    %}    
    
    % 用直線方程式求出候選區域的方向
    angle = atand( cfun.p1 );
    % 依照方向與特徵點分佈設定候選區域的四個點座標
    rot_upper_left(2) = left_axis_point(2) + (  upper_bound_dist * sind(angle) );
    rot_upper_left(1) = left_axis_point(1) + ( -upper_bound_dist * cosd(angle) );

    rot_lower_left(2) = left_axis_point(2) + ( -lower_bound_dist * sind(angle) );
    rot_lower_left(1) = left_axis_point(1) + (  lower_bound_dist * cosd(angle) );

    rot_upper_right(2) = left_axis_point(2) + (  dist_bet_points * cosd(angle)  + upper_bound_dist * sind(angle) );
    rot_upper_right(1) = left_axis_point(1) + ( -upper_bound_dist * cosd(angle) + dist_bet_points * sind(angle) );

    rot_lower_right(2) = left_axis_point(2) + ( dist_bet_points * cosd(angle)  - lower_bound_dist * sind(angle) );
    rot_lower_right(1) = left_axis_point(1) + ( lower_bound_dist * cosd(angle) + dist_bet_points * sind(angle) );
    
    % 畫出候選區域    
    %{ 
    line( [rot_upper_left(2), rot_upper_right(2)], ...
             [rot_upper_left(1), rot_upper_right(1)], 'Color', 'c','LineWidth',2);
    line( [rot_upper_left(2), rot_lower_left(2)], ...
             [rot_upper_left(1), rot_lower_left(1)], 'Color', 'c','LineWidth',2);
    line( [rot_lower_right(2), rot_upper_right(2)], ...
             [rot_lower_right(1), rot_upper_right(1)], 'Color', 'c','LineWidth',2);     
    line( [rot_lower_right(2), rot_lower_left(2)], ...
             [rot_lower_right(1), rot_lower_left(1)], 'Color', 'c','LineWidth',2);  
    %}
    
    candidate_ROI = [candidate_ROI; rot_upper_left(2) rot_upper_left(1) rot_lower_left(2) rot_lower_left(1) ...
                                                   rot_upper_right(2) rot_upper_right(1) rot_lower_right(2) rot_lower_right(1)];
    
    % weak (特徵點小於3個無法設定座標時的處理)
    if size(points_inliers,1) <= 2
        most_top = min(points_inliers(:,1));
        most_bottom = max(points_inliers(:,1));
        most_left = min(points_inliers(:,2));
        most_right = max(points_inliers(:,2));
        
        candidate_ROI(end,:) = [ most_left-1 most_top most_left-1 most_bottom ...
                                 most_right+1 most_top most_right+1 most_bottom ];
    end
    
    % 用連續線段表示一個 cluster   
    plot(points_inliers(:,2), ...
        points_inliers(:,1), ...
            '-', 'Color', color(i,:), 'lineWidth',2);
        
end

hold off;

%% ROI extraction

exacted_ROI = zeros( size(candidate_ROI,1), 8 );

for i = 1:size(candidate_ROI,1)
    
    intermedium = ROI_extract( im, candidate_ROI(i,:), data );
    
    if intermedium ~= 0
        exacted_ROI(i,:) = intermedium;
    else
        exacted_ROI(i,:) = [];
    end
    
    
end

% 顯示最後 ROI 選擇結果，並給定 handle 供 main 函數儲存
fig_handle = figure(8);
imshow(im);
hold on;

for i = 1:size(exacted_ROI,1)
    line([exacted_ROI(i,1) exacted_ROI(i,3)], [exacted_ROI(i,2) exacted_ROI(i,4)], 'Color', 'c', 'LineWidth', 2);
    line([exacted_ROI(i,3) exacted_ROI(i,7)], [exacted_ROI(i,4) exacted_ROI(i,8)], 'Color', 'c', 'LineWidth', 2);
    line([exacted_ROI(i,1) exacted_ROI(i,5)], [exacted_ROI(i,2) exacted_ROI(i,6)], 'Color', 'c', 'LineWidth', 2);
    line([exacted_ROI(i,7) exacted_ROI(i,5)], [exacted_ROI(i,8) exacted_ROI(i,6)], 'Color', 'c', 'LineWidth', 2);
end

hold off;
%}

end

