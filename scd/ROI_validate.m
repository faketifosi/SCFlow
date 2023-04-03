function accumulated_error = ROI_validate( ROI )
% �H����.������v�ƦC�W�h���� ROI �O�_�ŦX�λݲ���
%
    global ROI_property;
    
    horizontal_align_rule = 0;
	vertical_align_rule = 0;

    level = graythresh(ROI);
    BW = im2bw(ROI,level);
    
    % truncate removal (����ťհϰ�)
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
    
    BW = imresize(BW, [100 (size(BW,2)/size(BW,1))*100]);
    
    % ROI�������P������v
    hor_hist = zeros( size(BW,1),1 );
    for i = 1:size(BW,1)
        hor_hist(i) = sum( BW(i,:) == 0 );
    end

    ver_hist = zeros( 1,size(BW,2),1 );
    for i = 1:size(BW,2)
        ver_hist(i) = sum( BW(:,i) == 0 );
    end
        
    atRegion = false;
    interval_area_seq = []; interval = 0;
    ver_hist = ver_hist( find(ver_hist>2, 1, 'first'):find(ver_hist>2, 1, 'last') );

    % ���������϶��ܴ�
    for i = 1:size(ver_hist,2)
        if ver_hist(i) > 2 && ~atRegion 
            if interval ~= 0
                interval_area_seq = [interval_area_seq interval];
                interval = 0;
            end
            atRegion = true;
            interval = interval + 1; 
        elseif ver_hist(i) > 2 && atRegion
            interval = interval + 1; 
        elseif ~(ver_hist(i) > 2) && ~atRegion
            interval = interval + 1; 
        elseif ~(ver_hist(i) > 2) &&  atRegion
            if interval ~= 0
                interval_area_seq = [interval_area_seq interval];
                interval = 0;
            end
            atRegion = false;
            interval = interval + 1; 
        end

        if i == size(ver_hist,2)
            interval_area_seq = [interval_area_seq interval];
        end       
    end

    % �p������F��϶���ȧǦC
    if size(interval_area_seq,2) > 1
        horizontal_align_rule = interval_area_seq(1:end-1) ./ interval_area_seq(2:end);
    end

    % ���������϶��ܴ�
    atRegion = false;
    interval_area_seq = []; interval = 0;
    hor_hist = hor_hist( find(hor_hist>2, 1, 'first'):find(hor_hist>2, 1, 'last') );
    for i = 1:size(hor_hist,1)
        if hor_hist(i) > 2 && ~atRegion 
            if interval ~= 0
                interval_area_seq = [interval_area_seq interval];
                interval = 0;
            end
            atRegion = true;
            interval = interval + 1; 
        elseif hor_hist(i) > 2 && atRegion
            interval = interval + 1; 
        elseif ~(hor_hist(i) > 2) && ~atRegion
            interval = interval + 1; 
        elseif ~(hor_hist(i) > 2) &&  atRegion
            if interval ~= 0
                interval_area_seq = [interval_area_seq interval];
                interval = 0;
            end
            atRegion = false;
            interval = interval + 1; 
        end

        if i == size(hor_hist,1)
            interval_area_seq = [interval_area_seq interval];
        end       
    end

    % �p�⫫���F��϶���ȧǦC
    if size(interval_area_seq,2) > 1
        vertical_align_rule = interval_area_seq(1:end-1) ./ interval_area_seq(2:end);
    end
    
    if (size(horizontal_align_rule,2) > size(ROI_property.horizontal_align_rule,2)) ...
            || (horizontal_align_rule(1) == 0)
        accumulated_error = 0;  % ����0�N��L�k����
        return;
    end

    % ��ȧǦC������ correlation
    min_SSD = 100;
    for i = 1:size(ROI_property.horizontal_align_rule,2) - size(horizontal_align_rule,2) + 1
        SSD = sum( abs(ROI_property.horizontal_align_rule(i:i+size(horizontal_align_rule,2)-1) - horizontal_align_rule) );
        if SSD < min_SSD
            min_SSD = SSD;
        end
    end
    
    accumulated_error = min_SSD * ( size(ROI_property.horizontal_align_rule,2) / size(horizontal_align_rule,2) );
end

