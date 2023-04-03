function [] = SIFT_clustering_ROI( object_fileName )

global fig_handle;       % ���� figure handle, �s�ɤ���
global ref_descriptors;  % �z��᪺�S�x�I
global ref_locations;    % �z��᪺�S�x�I�y��
global file;             % �ɮ׽s��, �s�ɤ���

% [�ѦҼv��, �S�x�y�z�l, �S�x�I�y��]
[im, des, loc] = sift( object_fileName );

% SIFT �{�w�S�x�I�ǰt���Z�����e��(�ۦ���)
distRatio = 0.8; 

%
% �@�ӯS�x�I��h�ӹ����I
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

% �@�ӯS�x�I�u��@�ӹ����I
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
% �h�����I�ĥ�
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
% �@�ӯS�x�I�u���@�ӹ����I�ĥ�
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

%�e�X�S�x�I
fig_handle = figure(1); % show sift feature point
imshow(im, 'border', 'tight', 'initialmagnification', 'fit');
%set(gca,'Units','normalized','Position',[0 0 1 1]);  %# Modify axes size
set(fig_handle,'Position',[150 600 size(im,2) size(im,1)]);  %# Modify figure size

hold on;
plot(data(:,2), data(:,1), 'go', 'lineWidth', 2);
hold off;

%% Estimate candidate 
% �� clustering ���R���G�U�� cluster �������s�I�è̷Ӥ��G�]�w��B���Կ�ϰ�

global xOrdered;    % ���s���G�������ܼơA��Ƹg���s�ᤧ���� (�b optics_clustering �禡���ާ@ )

% �ư��y�Ц�m���ƪ��S�x�I
data = unique(data, 'rows');
% �S�x�I�y�п�J 
clusters = optics_clustering( data, im );

% �e�X clusters
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

% �ӧO�e�X cluster �� �Կ�ϰ�
for i = 1:numel(clusters)

    cluster = xOrdered(clusters(i).element(1):clusters(i).element(2),:);
  
    iterative = true; iter = 1;
    
    % �̶��ǨD�X��⤧���ڦ��Z����
    distance_map = (cluster(1:end-1,2) - cluster(2:end,2)).^2 + (cluster(1:end-1,1) - cluster(2:end,1)).^2;
    % �p��觡��
    dist_rms_sum = sum( distance_map );    
    dist_rms_sum = ( dist_rms_sum / (size(cluster,1)-1) )^0.5;
    
    % �̦h���N�T�������P�觡�ڬۮt�L�j���ݵu
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

    % �Ĥ@���� line fitting
    [cfun gof] = fit(cluster(:,2), cluster(:,1),'poly1');
    plot( xOrdered([clusters(i).element(1):clusters(i).element(2)],2), xOrdered([clusters(i).element(1):clusters(i).element(2)],1), 'b+', 'linewidth', 2 );

    % plot( cfun, 'b' );    % �H�Ŧ�u��ܲĤ@�� line fitting ���G
    axis off;
    % xlabel('');
    % ylabel('');

    % �p��Ҧ��I�M�Ĥ@�� fitting �����u���Z�����觡��
    point_dist = abs( (cfun.p1 * cluster(:,2) - cluster(:,1) + cfun.p2) / (cfun.p1^2 + 1)^0.5 );

    % �R���Z���ӻ������s�I�ð���ĤG�� line fitting
    if size(cluster,1) > 2
        points_inliers = cluster( find(point_dist <= 2*gof.rmse), : );
        [cfun gof] = fit(points_inliers(:,2), points_inliers(:,1), 'poly1');
    else
        points_inliers = cluster;
    end
 
    % �b�v���W��ܲĤG�� fitting ���G�P �ѤU���I
    % points_inliers = cluster;
    plot( points_inliers(:,2),points_inliers(:,1),'yo', 'linewidth', 2 );
    % plot( cfun, 'g' );
    % xlabel(' ');
    % ylabel(' ');
    
    inliers_dist = (cfun.p1 * points_inliers(:,2) - points_inliers(:,1) + cfun.p2) / (cfun.p1^2 + 1)^0.5;
    
    % �̥��A�̥k�A�̤W�A�̤U���I
    most_left_point   = points_inliers( find( points_inliers(:,2) == min(points_inliers(:,2)), 1 ), : );
    most_right_point  = points_inliers( find( points_inliers(:,2) == max(points_inliers(:,2)), 1 ), : );
    %{
    most_top_point    = points_inliers( find( inliers_dist == max(inliers_dist) ), : );
    most_bottom_point = points_inliers( find( inliers_dist == min(inliers_dist) ), : );
    %}    
    
    % �o�̥��I�Φ��خؤ������
    p1(2) = most_left_point(2);
    p1(1) = cfun.p1 * most_left_point(2) + cfun.p2;     % x �y�бa�J��{���D y
    p2(2) = most_right_point(2);      
    p2(1) = cfun.p1 * most_right_point(2) + cfun.p2;    % x �y�бa�J��{���D y
        
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
    
    % �Ϊ��u��{���D�X�Կ�ϰ쪺��V
    angle = atand( cfun.p1 );
    % �̷Ӥ�V�P�S�x�I���G�]�w�Կ�ϰ쪺�|���I�y��
    rot_upper_left(2) = left_axis_point(2) + (  upper_bound_dist * sind(angle) );
    rot_upper_left(1) = left_axis_point(1) + ( -upper_bound_dist * cosd(angle) );

    rot_lower_left(2) = left_axis_point(2) + ( -lower_bound_dist * sind(angle) );
    rot_lower_left(1) = left_axis_point(1) + (  lower_bound_dist * cosd(angle) );

    rot_upper_right(2) = left_axis_point(2) + (  dist_bet_points * cosd(angle)  + upper_bound_dist * sind(angle) );
    rot_upper_right(1) = left_axis_point(1) + ( -upper_bound_dist * cosd(angle) + dist_bet_points * sind(angle) );

    rot_lower_right(2) = left_axis_point(2) + ( dist_bet_points * cosd(angle)  - lower_bound_dist * sind(angle) );
    rot_lower_right(1) = left_axis_point(1) + ( lower_bound_dist * cosd(angle) + dist_bet_points * sind(angle) );
    
    % �e�X�Կ�ϰ�    
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
    
    % weak (�S�x�I�p��3�ӵL�k�]�w�y�Юɪ��B�z)
    if size(points_inliers,1) <= 2
        most_top = min(points_inliers(:,1));
        most_bottom = max(points_inliers(:,1));
        most_left = min(points_inliers(:,2));
        most_right = max(points_inliers(:,2));
        
        candidate_ROI(end,:) = [ most_left-1 most_top most_left-1 most_bottom ...
                                 most_right+1 most_top most_right+1 most_bottom ];
    end
    
    % �γs��u�q��ܤ@�� cluster   
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

% ��̫ܳ� ROI ��ܵ��G�A�õ��w handle �� main ����x�s
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

