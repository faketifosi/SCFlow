function [ exact_ROI ] = ROI_extract( im, candidate_ROI, SIFT_point )
% 車牌的 ROI 偵測函式
% candidate_ROI = (x1,y1,x2,y2,x3,y3,x4,y4);

step = 1; % 純粹記錄迭代次數

global ROI_property;
global number_of_object;
global file;

% mkdir( strcat('test sample\car plate dataset\saveas\', num2str(file) ) );
% 建立與檔案編號相同的存檔目錄

    % 縮小範圍，只留下候選區域附近範圍
    middleX = round(( candidate_ROI(5) + candidate_ROI(1) ) / 2);
    middleY = round(( candidate_ROI(4) + candidate_ROI(2) ) / 2); 
    plate = [middleX-100 middleY-50 middleX+100 middleY+50];
    % plate = [ 左邊界X座標 上邊界Y座標 右邊界X座標 下邊界Y座標 ]
    
    if plate(1) < 1
        plate(1) = 1;
    elseif plate(2) < 1
        plate(2) = 1;
    elseif plate(3) > size(im,2)
        plate(3) = size(im,2);
    elseif plate(4) > size(im,1)
        plate(4) = size(im,1);        
    end
    
    plate = round(plate);
    
    im_ori = im;
    im_temp = im;
    im(:) = 255;
    

    im_temp = im_temp(plate(2):plate(4),plate(1):plate(3));
    im_temp = imadjust(im_temp);
        
 
    
    % 取大塊白色連通元件(有可能為車牌)　因整體結果稍差，預設為不採用
    %{
    CCs = bwconncomp(BW_im,8);
    CCp  = regionprops(CCs);
    
    maxArea = 0;
    max_i = 0;
    
    if size(CCp,1) >= 1
        for i = size(CCp,1):-1:1
            area = CCp(i).BoundingBox(3) * CCp(i).BoundingBox(4);
            aspect_ratio = CCp(i).BoundingBox(3) / CCp(i).BoundingBox(4);
            
            if area > maxArea && aspect_ratio < 5;
                maxArea = area;
                max_i = i;
            end
                
        end
    end
 
    % 從顏色濾掉太白不可能為字元的物體
    im_temp(im_temp > 100) = 255;
    % 大塊白色物體的範圍，用於篩選出可能為車牌部分
    bounding = round([CCp(max_i).BoundingBox(2) CCp(max_i).BoundingBox(2)+CCp(max_i).BoundingBox(4)-1 ...
                     CCp(max_i).BoundingBox(1) CCp(max_i).BoundingBox(1)+CCp(max_i).BoundingBox(3)-1]);
            
    CCs = bwconncomp(1-BW_im,4);
    CCp  = regionprops(CCs);
    
    if size(CCp,1) >= 1
        for i = size(CCp,1):-1:1
            if CCp(i).Area > 2500
                im_temp(CCs.PixelIdxList{i}) = 255;
            end
        end
    end   
    
    im(plate(2) + bounding(1):plate(2) + bounding(2), plate(1) + bounding(3):plate(1) + bounding(4)) = im_temp(bounding(1):bounding(2), bounding(3):bounding(4));
    %}    
    
    im(plate(2):plate(4),plate(1):plate(3)) = im_temp;


    totalRotAngle = 0;      %累計當前ROI對原圖總共的旋轉角度

    im_center_x = size(im,2) / 2;   %目標影像的座標中心
    im_center_y = size(im,1) / 2;

       
    theta = 0; % 車牌開始不旋轉，容易出錯
    rot_im = imrotate(im,theta,'bilinear','loose');     %輸入影像依照初次ROI角度旋轉以便存取操作

    
    rot_im_ori = imrotate(im_ori,theta,'bilinear','loose');

    rot_im_center_x = size(rot_im,2) / 2;   % 旋轉過後影像中心
    rot_im_center_y = size(rot_im,1) / 2;

    theta = -theta;
    totalRotAngle = totalRotAngle + theta;
    
    % 旋轉過後的ROI四個頂點
    UL_X = rot_im_center_x +  (candidate_ROI(1)-im_center_x) * cosd(theta) - (candidate_ROI(2)-im_center_y) * sind(theta);
    UL_Y = rot_im_center_y +  (candidate_ROI(2)-im_center_y) * cosd(theta) + (candidate_ROI(1)-im_center_x) * sind(theta);
    %{
    LL_X = rot_im_center_x +  (candidate_ROI(3)-im_center_x) * cosd(theta) - (candidate_ROI(4)-im_center_y) * sind(theta);
    LL_Y = rot_im_center_y +  (candidate_ROI(4)-im_center_y) * cosd(theta) + (candidate_ROI(3)-im_center_x) * sind(theta);

    UR_X = rot_im_center_x +  (candidate_ROI(5)-im_center_x) * cosd(theta) - (candidate_ROI(6)-im_center_y) * sind(theta);
    UR_Y = rot_im_center_y +  (candidate_ROI(6)-im_center_y) * cosd(theta) + (candidate_ROI(5)-im_center_x) * sind(theta);
    
    LR_X = rot_im_center_x +  (candidate_ROI(7)-im_center_x) * cosd(theta) - (candidate_ROI(8)-im_center_y) * sind(theta);
    LR_Y = rot_im_center_y +  (candidate_ROI(8)-im_center_y) * cosd(theta) + (candidate_ROI(7)-im_center_x) * sind(theta);
    %}   
       
    % 當前 ROI 的原點.高寬資訊
    ROI_rect_ori = round([UL_X UL_Y]);
    ROI_width  = round( ((candidate_ROI(1) - candidate_ROI(5))^2 + (candidate_ROI(2) - candidate_ROI(6))^2 )^0.5 );
    ROI_height = round( ((candidate_ROI(1) - candidate_ROI(3))^2 + (candidate_ROI(2) - candidate_ROI(4))^2 )^0.5 );
   
    % 一開始的 ROI 若過小則稍微加大
    if ROI_width < 10 
        ROI_width = ROI_width + 10;
    end
    
    if ROI_height < 10 
        ROI_height = ROI_height + 10;
    end
    
    iterative = true;   % 控制迭代繼續與否之旗標
    chance = true;  % "太早成為失敗結果則給予一次機會"的控制旗標
    shifted = false;    % 防止連續移動的控制旗標
    right_adjust = false;   % 強制往右移動控制旗標
    left_adjust = false;    % 強制往左移動控制旗標
    fit = false;    % 用於旋轉後貼合當前 ROI 內容的控制旗標
    rotated = false;    % 防止連續兩次迭代做旋轉處理的控制旗標
    rotate_count = 0;   % 累計旋轉校正次數以防無止盡處理的控制旗標
    
    % 進入迭代 fit ROI 程序
    while iterative
        
        iterative = false;
        
        fh = figure(3);
        imshow(im, 'border', 'tight', 'initialmagnification', 'fit');
        set (fh,'Position',[805,600,640,360]);
        hold on;
        
        % 計算此字迭代的 ROI 對於原圖的四頂點座標位置
        ROI2im_x1 = round( im_center_x + (ROI_rect_ori(1)-rot_im_center_x) * cosd(-totalRotAngle) - (ROI_rect_ori(2)-rot_im_center_y) * sind(-totalRotAngle) );
        ROI2im_y1 = round( im_center_y + (ROI_rect_ori(2)-rot_im_center_y) * cosd(-totalRotAngle) + (ROI_rect_ori(1)-rot_im_center_x) * sind(-totalRotAngle) );

        ROI2im_x2 = round( im_center_x + (ROI_rect_ori(1)+ROI_width-rot_im_center_x) * cosd(-totalRotAngle) - (ROI_rect_ori(2)-rot_im_center_y) * sind(-totalRotAngle) );
        ROI2im_y2 = round( im_center_y + (ROI_rect_ori(2)-rot_im_center_y) * cosd(-totalRotAngle) + (ROI_rect_ori(1)+ROI_width-rot_im_center_x) * sind(-totalRotAngle) );

        ROI2im_x3 = round( im_center_x + (ROI_rect_ori(1)-rot_im_center_x) * cosd(-totalRotAngle) - (ROI_rect_ori(2)+ROI_height-rot_im_center_y) * sind(-totalRotAngle) );
        ROI2im_y3 = round( im_center_y + (ROI_rect_ori(2)+ROI_height-rot_im_center_y) * cosd(-totalRotAngle) + (ROI_rect_ori(1)-rot_im_center_x) * sind(-totalRotAngle) );

        ROI2im_x4 = round( im_center_x + (ROI_rect_ori(1)+ROI_width-rot_im_center_x) * cosd(-totalRotAngle) - (ROI_rect_ori(2)+ROI_height-rot_im_center_y) * sind(-totalRotAngle) );
        ROI2im_y4 = round( im_center_y + (ROI_rect_ori(2)+ROI_height-rot_im_center_y) * cosd(-totalRotAngle) + (ROI_rect_ori(1)+ROI_width-rot_im_center_x) * sind(-totalRotAngle) );

        % 顯示目前 ROI 在原始影像上的區域
        line([ROI2im_x1 ROI2im_x2],[ROI2im_y1 ROI2im_y2],'Color', 'c','LineWidth',2);
        line([ROI2im_x2 ROI2im_x4],[ROI2im_y2 ROI2im_y4],'Color', 'c','LineWidth',2);
        line([ROI2im_x1 ROI2im_x3],[ROI2im_y1 ROI2im_y3],'Color', 'c','LineWidth',2);
        line([ROI2im_x4 ROI2im_x3],[ROI2im_y4 ROI2im_y3],'Color', 'c','LineWidth',2);
        hold off;
        
        %控制邊界，若ROI的調整超出影像範圍則直接跳出(暫時沒處理, 之後可改進, 目前溢出則直接停止)
        if ROI2im_x1 < 1 || ROI2im_x1 > size(im,2) || ROI2im_x2 < 1 || ROI2im_x2 > size(im,2) || ROI2im_x3 < 1 || ...
                ROI2im_x3 > size(im,2) || ROI2im_x4 < 1 || ROI2im_x4 > size(im,2) || ROI2im_y1 < 1 || ROI2im_y1 > size(im,1) || ...
                ROI2im_y2 < 1 || ROI2im_y2 > size(im,1) || ROI2im_y3 < 1 || ROI2im_y3 > size(im,1) || ROI2im_y4 < 1 || ROI2im_y4 > size(im,1)
            exact_ROI = [ROI2im_x1 ROI2im_y1 ROI2im_x2 ROI2im_y2 ROI2im_x3 ROI2im_y3 ROI2im_x4 ROI2im_y4];
            return;
        end
        
        % 存出某個迭代階段在原影像中的ROI狀態
        %{
        print( fh, strcat('test sample\car plate dataset\saveas\', num2str(file) ,'\ori-step', num2str(step), '.eps'), '-depsc' );
        saveas(fh, strcat('test sample\car plate dataset\saveas\', num2str(file) ,'\ori-step', num2str(step), '.jpg') );
        %}      
        
        % 在旋轉後的影像上顯示目前取得的 ROI
        fh = figure(4);
        imshow(rot_im_ori, 'border', 'tight', 'initialmagnification', 'fit');
        set (fh,'Position',[805,135,640,360]);
        hold on;
        line([ROI_rect_ori(1) ROI_rect_ori(1)+ROI_width],[ROI_rect_ori(2) ROI_rect_ori(2)],'Color', 'c','LineWidth',2);
        line([ROI_rect_ori(1) ROI_rect_ori(1)],[ROI_rect_ori(2) ROI_rect_ori(2)+ROI_height],'Color', 'c','LineWidth',2);
        line([ROI_rect_ori(1)+ROI_width ROI_rect_ori(1)+ROI_width],[ROI_rect_ori(2) ROI_rect_ori(2)+ROI_height],'Color', 'c','LineWidth',2);
        line([ROI_rect_ori(1) ROI_rect_ori(1)+ROI_width],[ROI_rect_ori(2)+ROI_height ROI_rect_ori(2)+ROI_height],'Color', 'c','LineWidth',2);
        hold off;
        
        % 存出某個迭代階段在旋轉後影像中的ROI狀態
        %{        
        print( fh, strcat('test sample\car plate dataset\saveas\', num2str(file) ,'\rot-step', num2str(step), '.eps'), '-depsc' );
        saveas(fh, strcat('test sample\car plate dataset\saveas\', num2str(file) ,'\rot-step', num2str(step), '.jpg') );
        %}
        
        % 從旋轉後影像中取出 ROI pixel 內容
        ROI_rect_ori = round(ROI_rect_ori);
        ROI = rot_im( [ROI_rect_ori(2):(ROI_rect_ori(2)+ROI_height)], [ROI_rect_ori(1):(ROI_rect_ori(1)+ROI_width)] );
        
        % image enhancement
        H = fspecial('gaussian');
        ROI = imfilter(ROI,H,'replicate');
        ROI = imadjust(ROI);
        H = fspecial('unsharp');
        ROI = imfilter(ROI,H,'replicate');
        % end of image enhancement

        % 只取有edge的區域做二值化
        Canny_edge = edge(ROI,'canny');
        map = zeros(size(ROI), 'uint8');
        BW_ROI = zeros(size(ROI), 'uint8');
        BW_ROI = 255 - BW_ROI;
        
        CCs = bwconncomp(Canny_edge,8);
        CCp  = regionprops(CCs);

        for i = 1:size(CCp,1)
            map( ceil(CCp(i).BoundingBox(2)):ceil(CCp(i).BoundingBox(2))+CCp(i).BoundingBox(4)-1, ...
                    ceil(CCp(i).BoundingBox(1)):ceil(CCp(i).BoundingBox(1))+CCp(i).BoundingBox(3)-1) = 128;
        end
        
        % 找包含所有 edge 的最小區域做裁減
        i = 1; 
        top = 0;
        while sum(Canny_edge(i,:)) == 0 && i < size(Canny_edge,1)
        i = i+1;
        top = i;
        end

        i = size(ROI,1);
        bottom = 0;
        while sum(Canny_edge(i,:)) == 0 && i > 1
        i = i-1;
        bottom = i;
        end

        i = 1;
        left = 0;
        while sum(Canny_edge(:,i)) == 0 && i < size(Canny_edge,2)
        i = i + 1;
        left = i;
        end

        i = size(ROI,2); 
        right = 0;
        while sum(Canny_edge(:,i)) == 0 && i > 1
        i = i - 1;
        right = i;
        end
        
        % 太接近原ROI影像邊界就改回邊界值，否則效果不好
        if top - 1 < 3
            top = 1;
        end
        
        if size(ROI,1) - bottom < 3
            bottom = size(ROI,1);
        end
        
        if left - 1 < 3
            left = 1;
        end
        
        if size(ROI,2) - right < 3
            right = size(ROI,2);
        end
        
        %　Otsu 二值化
        BW_ROI(top:bottom,left:right) = ROI(top:bottom,left:right);
        BW_ROI = im2bw(BW_ROI, graythresh( ROI(find(map==128)) ));
                      
        BW_ROI = 1 - BW_ROI;
        % connected component labeling
        CCs = bwconncomp(BW_ROI,8);
        CCp  = regionprops(CCs);
        
        % ROI 二值化之後沒任何內容直接跳出
        if size(CCp,1) < 1
            exact_ROI = 0;
            return;
        end
        
        % 移除雜訊 長寬比或大小與內容差太多則過濾
        if size(CCp,1) > 1
            for i = size(CCp,1):-1:1
                if CCp(i).Area < 5 || CCp(i).BoundingBox(3) / CCp(i).BoundingBox(4) > 1
      
                    if size(CCp,1) ~= 1
                        CCp(i) = [];
                        CCs.PixelIdxList(i) = [];
                    end
                                       
                end
            end
        end
        
        % add for car 
        edge_image = edge(BW_ROI,'canny');
        edge_hist = zeros(size(edge_image,2),1);
        
        % 計算 edge pixel 的垂直投影
        for i = 1:size(edge_image,2)
            edge_hist(i) = sum(edge_image(:,i));
        end
                     
        %{ 
        初始化最大 component 變數 (作為之後 ROI之篩選.擴張.移動.旋轉 之參考目標)
        maxAreaCC = 0;    maxArea = 0;   
        % 取得面積最大之 component
        for i = 1:size(CCp,1)
            area = CCp(i).BoundingBox(3) * CCp(i).BoundingBox(4);
            if area > maxArea
                maxArea = area;
                maxAreaCC = i;
            end
        end
        %}
        
        % 尋找 median area component
        CC_tempSeq = zeros(size(CCp,1),1);
        for i = 1:size(CCp,1)
            CC_tempSeq(i) = [CCp(i).BoundingBox(3) * CCp(i).BoundingBox(4)];
        end
        
        % 計算面積適中的 component
        [CC_sortByArea index] = sort(CC_tempSeq);
        maxAreaCC = index( floor(size(index,1)/2) + 1 );
        maxArea = CC_tempSeq(maxAreaCC);
        
        % 紀錄面積最大的 component
        maxAreaCC_struct = CCp(maxAreaCC);
        
        % 初始 map 變數成全黑影像
        map = zeros(size(ROI));
                
        quantity = 0;    % number of character ("目前"階段的ROI中的物體總數) 
        skewErrTop = 0; skewErrBot = 0;     % 累積傾斜誤差

        % 以最大面積 component 為參考篩選大小過小的 component
        % 並計算各別 component 對於最大 component 的上下高度累計誤差, 做為評估旋轉之用
        for i = size(CCp,1):-1:1
            area = CCp(i).BoundingBox(3) * CCp(i).BoundingBox(4);
            if abs(area - maxArea) < maxArea*0.6 
                map(CCs.PixelIdxList{i}) = 1;
                quantity = quantity + 1;
                skewErrTop = skewErrTop + abs( CCp(i).BoundingBox(2) - maxAreaCC_struct.BoundingBox(2) );
                skewErrBot = skewErrBot + abs( (CCp(i).BoundingBox(2) + CCp(i).BoundingBox(4) - 1) - (maxAreaCC_struct.BoundingBox(2) + maxAreaCC_struct.BoundingBox(4) - 1) );
            else
                CCp(i) = [];
            end
        end
        
        % ROI的水平與垂直投影
        hor_hist = zeros( size(BW_ROI,1),1 );
        for i = 1:size(BW_ROI,1)
            hor_hist(i) = sum( BW_ROI(i,:) );
        end
        
        ver_hist = zeros( 1,size(BW_ROI,2) );
        for i = 1:size(BW_ROI,2)
            ver_hist(i) = sum( BW_ROI(:,i) );
        end
           
        % 顯示二值化並篩選後的影像
        fh = figure(5);
        imshow(map, 'border', 'tight', 'initialmagnification', 'fit');   
        set(fh,'Position',[1463,600, size(map,2)*2.5, size(map,1)*2.5]);   
        
        % 顯示二值化並篩選後的影像
        %{        
        print( fh, strcat('test sample\car plate dataset\saveas\', num2str(file) ,'\map-step', num2str(step), '.eps'), '-depsc' );
        saveas(fh, strcat('test sample\car plate dataset\saveas\', num2str(file) ,'\map-step', num2str(step), '.jpg') );
        %}      

       %% false positive elimination　（ROI狀態與參考對象比例超出容許範圍則停止）
        if (size(ROI,2) / maxAreaCC_struct.BoundingBox(3) > ROI_property.ROI_to_CCs_ratio.widthRatio * 3.5) ...           % 2.5
                || (size(ROI,1) / maxAreaCC_struct.BoundingBox(4) > ROI_property.ROI_to_CCs_ratio.heightRatio * 5) ...    % 3 or 4 
                || (( size(ROI,2) / size(ROI,1) ) > ROI_property.aspect_ratio * 1.5) && (size(ROI,1)*size(ROI,2) > 500)
            break;
        end
                 
       %% rotate
        % 累計誤差大於最大 component 之高度某個程度即旋轉
        if skewErrTop >= maxAreaCC_struct.BoundingBox(4)*0.5 && skewErrBot >= maxAreaCC_struct.BoundingBox(4)*0.5 && ~rotated && rotate_count < 10 %限制次數上限
            
            maxAreaCC = 0;    maxArea = 0;
        
            for i = 1:size(CCp,1)
                area = CCp(i).BoundingBox(3) * CCp(i).BoundingBox(4);
                if area > maxArea
                    maxAreaCC = i;
                    maxArea = area;
                end
            end
                                 
            if maxAreaCC > 1    % 避免超出存取之條件 (以最大面積 component 元件為基準往左參考)
                hypotenuse = ( (CCp(maxAreaCC).BoundingBox(1) - CCp(maxAreaCC-1).BoundingBox(1))^2 + (CCp(maxAreaCC).BoundingBox(2) - CCp(maxAreaCC-1).BoundingBox(2))^2 )^0.5;
                adjustAngle = acosd( abs(CCp(maxAreaCC).BoundingBox(1) - CCp(maxAreaCC-1).BoundingBox(1)) / hypotenuse );
                if CCp(maxAreaCC).BoundingBox(2) < CCp(maxAreaCC-1).BoundingBox(2)
                    adjustAngle = -adjustAngle;
                end
            else
                hypotenuse = ( (CCp(maxAreaCC).BoundingBox(1) - CCp(maxAreaCC+1).BoundingBox(1))^2 + (CCp(maxAreaCC).BoundingBox(2) - CCp(maxAreaCC+1).BoundingBox(2))^2 )^0.5;
                adjustAngle = acosd( abs(CCp(maxAreaCC).BoundingBox(1) - CCp(maxAreaCC+1).BoundingBox(1)) / hypotenuse );
                if CCp(maxAreaCC+1).BoundingBox(2) < CCp(maxAreaCC).BoundingBox(2)
                    adjustAngle = -adjustAngle;
                end
            end    
            
            if adjustAngle ~= 0 %若評估旋轉角不為０，則旋轉並設定迭代
            
                iterative = true;
                                          
                adjustAngle = -adjustAngle;
                totalRotAngle = totalRotAngle + adjustAngle;
                
                rot_im = imrotate(im, -totalRotAngle,'bilinear','loose');   % 旋轉校正

                ori_im_center_x = rot_im_center_x;   % 旋轉前影像中心
                ori_im_center_y = rot_im_center_y;

                rot_im_center_x = size(rot_im,2) / 2;   % 旋轉後影像中心
                rot_im_center_y = size(rot_im,1) / 2; 

                tempORI(1) = round( rot_im_center_x + (ROI_rect_ori(1)-ori_im_center_x) * cosd(adjustAngle) - (ROI_rect_ori(2)-ori_im_center_y) * sind(adjustAngle) );
                tempORI(2) = round( rot_im_center_y + (ROI_rect_ori(2)-ori_im_center_y) * cosd(adjustAngle) + (ROI_rect_ori(1)-ori_im_center_x) * sind(adjustAngle) );

                tempORI(3) = round( rot_im_center_x + (ROI_rect_ori(1)+ ROI_width -ori_im_center_x) * cosd(adjustAngle) - (ROI_rect_ori(2)+ ROI_height-ori_im_center_y) * sind(adjustAngle) );
                tempORI(4) = round( rot_im_center_y + (ROI_rect_ori(2)+ ROI_height-ori_im_center_y) * cosd(adjustAngle) + (ROI_rect_ori(1)+ ROI_width -ori_im_center_x) * sind(adjustAngle) );

                % 旋轉後 ROI 內容
                ROI_rect_ori(1) = round(( tempORI(1) + tempORI(3) ) / 2 - ROI_width  / 2);   % 當前 ROI 資訊
                ROI_rect_ori(2) = round(( tempORI(2) + tempORI(4) ) / 2 - ROI_height / 2);

                fit = true;  % 旋轉後調整 ROI 至服貼文字
                rotated = true;  % 控制不連續旋轉兩次的旗標   
                
                continue;    
            end
            
        end
        
        % 控制不連續旋轉兩次
        if rotated == true
            rotated = false;
        end
        
        % 累加旋轉次數，超過設定值則停止迭代
        rotate_count = rotate_count + 1;
        % end rotate                            

       %% expand. shift            
        
        % add for car (參考edge成分做延展及移動，取代原二值化影像之投影)
        ver_hist = edge_hist;
       
        if quantity < number_of_object % component 小於8個 向左或向右擴張
            
            % 從 map 考慮左右空間
            map_CC_margin = [ ceil(CCp(1).BoundingBox(1)) - 1 size(map,2) - ceil(CCp(end).BoundingBox(1)+CCp(end).BoundingBox(3)) ];
                               
            % 從原始 ROI 考慮左右空間
            left_margin =  find(ver_hist ~= 0, 1, 'first') - 1;
            right_margin = size(map,2) - find(ver_hist ~= 0, 1, 'last');
            
            right_expand = false;
            left_expand  = false;
            
            if isempty(left_margin)
                left_margin = 0;
            end
            
            if isempty(right_margin)
                right_margin = 0;
            end
            
            % SIFT map         
            % start SIFT map 
            
            trend = 0.5;
            
            if abs(left_margin - right_margin) < maxAreaCC_struct.BoundingBox(3)*0.2 || map_CC_margin(1) > size(map,2)/3 || map_CC_margin(2) > size(map,2)/3

                SIFT_map = zeros( size(rot_im) );

                SIFT_x = round( rot_im_center_x + (SIFT_point(:,2)-im_center_x) * cosd(totalRotAngle) - (SIFT_point(:,1)-im_center_y) * sind(totalRotAngle) );
                SIFT_y = round( rot_im_center_y + (SIFT_point(:,1)-im_center_y) * cosd(totalRotAngle) + (SIFT_point(:,2)-im_center_x) * sind(totalRotAngle) );

                SIFT_map( SIFT_y + (SIFT_x-1) * size(SIFT_map, 1) ) = 1; 
                
                ROI2SIFT = SIFT_map( ROI_rect_ori(2):(ROI_rect_ori(2)+ROI_height), ROI_rect_ori(1):(ROI_rect_ori(1)+ROI_width) );
                                    
                for i = 1:size(ROI2SIFT,2)
                    trend = trend + sum( ROI2SIFT(:,i) == 1 ) * i;
                end
                
                trend = trend / size( find(ROI2SIFT == 1),1 ) / size(ROI2SIFT,2);
 
                if trend > 0.5
                    right_expand = true;
                elseif trend < 0.5
                    left_expand = true;
                end

            end
            % end SIFT map            
                       
            if shifted   % 不連續 shift 兩次, 不然形成無限迴圈(反覆反向移動)
                shifted = false;
            end
            
            % 修正右移 (某一邊空白處太多往反向移動修正)
            if map_CC_margin(1) > size(map,2)/3 && ~iterative && ~right_adjust
                
                if ROI2im_x1 + ROI_width + map_CC_margin(1) <= size(im,2)
                    ROI_rect_ori(1) = ROI_rect_ori(1) + map_CC_margin(1);
                    iterative = true;
                    shifted = true;
                    right_adjust = true;
                end                                   
            % 修正左移
            elseif map_CC_margin(2) > size(map,2)/3 && ~iterative && ~left_adjust
                ROI_rect_ori(1) = ROI_rect_ori(1) - map_CC_margin(2);
                
                if ROI_rect_ori(1) <= 0
                    ROI_rect_ori(1) = 1;
                end
                
                iterative = true;
                shifted = true;
                left_adjust = true;
            end
            
            % 往右位移 (未滿足前面調整之條件則參考原始影像之兩側空白處移動)
            if left_margin >= maxAreaCC_struct.BoundingBox(3) && left_margin > right_margin*2 && ~iterative && shifted
                
                if ROI_rect_ori(1) + ROI_width + maxAreaCC_struct.BoundingBox(3) <= size(im,2)
                    ROI_rect_ori(1) = ROI_rect_ori(1) + maxAreaCC_struct.BoundingBox(3);
                    iterative = true;
                    shifted = true;
                end   
            % 往左位移
            elseif right_margin >= maxAreaCC_struct.BoundingBox(3) && right_margin > left_margin*2 && ~iterative && shifted
                ROI_rect_ori(1) = ROI_rect_ori(1) - maxAreaCC_struct.BoundingBox(3);
                
                if ROI_rect_ori(1) <= 0
                    ROI_rect_ori(1) = 1;
                end
                
                iterative = true;
                shifted = true;
            end
          
            % 往右延展，參考二值化並過濾雜訊後的影像垂直投影分部 與 特徵點趨勢 選擇往一方向擴展 ROI 大小                    
            if right_margin <= ( 1.5*maxAreaCC_struct.BoundingBox(3) ) && right_expand && ~iterative || (left_margin >= right_margin && ~left_expand)
                offset = size(im,2) - (ROI2im_x1 + ROI_width); % 控制溢出影像邊界(有誤差,沒處理很好)
                
                if ROI2im_x1 + ROI_width + round( 0.5*maxAreaCC_struct.BoundingBox(3) ) > size(im,2)
                    ROI_width = ROI_width + abs(offset);
                else
                    ROI_width = ROI_width + round( 0.5*maxAreaCC_struct.BoundingBox(3) );
                end
                
                if offset~=0
                    iterative = true;
                end
            % 往左延展
            elseif left_margin <= ( 1.5*maxAreaCC_struct.BoundingBox(3) ) && ~iterative
                offset = ROI2im_x1 - 1;
                ROI_rect_ori(1) = ROI_rect_ori(1) - 0.5*maxAreaCC_struct.BoundingBox(3);
                
                if ROI_rect_ori(1) <= 0
                    ROI_rect_ori(1) = 1;
                    ROI_width = ROI_width + offset;
                else
                    ROI_width = ROI_width + round( 0.5*maxAreaCC_struct.BoundingBox(3) );
                end
                
                if offset~=0
                    iterative = true;
                end            
            end  

        end
        
        % 旋轉後裁減空白處貼合目前所有 ROI 內容
        if fit
            fit = false;      
           
            i = 1;
            while sum( map(i, :) ) == 0 
                i = i + 1;
            end
            top = i;
            
            i = size(map,1);
            while sum( map(i, :) ) == 0 
                i = i - 1;
            end
            bottom = i;
            
            i = 1;
            while sum( map(:, i) ) == 0 
                i = i + 1;
            end
            left = i;
            
            i = size(map,2);
            while sum( map(:, i) ) == 0 
                i = i - 1;
            end
            right = i;
           
            ROI_rect_ori = [ROI_rect_ori + left ROI_rect_ori + top];         
            ROI_width = right - left + 1;
            ROI_height = bottom - top + 1;
            iterative = true;
            
        else
            if sum( map(size(map,1), :) ) > 0   % 下邊界包含 component 向下延展
                ROI_height = ROI_height + 2;
                iterative = true;
            end

            if sum( map(1, :) ) > 0     % 上邊界包含 component 向上延展
                ROI_rect_ori(2) = ROI_rect_ori(2) - 2;
                ROI_height = ROI_height + 2;
                iterative = true;
            end

            if sum( map(:, 1) ) > 0     % 左邊界包含 component 向左延展
                ROI_rect_ori(1) = ROI_rect_ori(1) - 2;
                ROI_width = ROI_width + 2;
                iterative = true;
            end

            if sum( map(:, size(map,2)) ) > 0    % 右邊界包含 component 向右延展
                ROI_width = ROI_width + 2;
                iterative = true;
            end            
        end

        % end if expand. shift
        
        % give some chance (都沒框到東西轉 90 度)
        if size(CCp,1) < 3 && chance && ~iterative
            chance = false;
            iterative = true;
                          
            adjustAngle = -90;
            rot_im = imrotate(rot_im,adjustAngle,'bilinear','loose');   % 旋轉校正

            ori_im_center_x = rot_im_center_x;   % 旋轉前影像中心
            ori_im_center_y = rot_im_center_y;

            rot_im_center_x = size(rot_im,2) / 2;   % 旋轉後影像中心
            rot_im_center_y = size(rot_im,1) / 2;

            adjustAngle = -adjustAngle;
            totalRotAngle = totalRotAngle + adjustAngle;
            
            
            tempORI(1) = round( rot_im_center_x + (ROI_rect_ori(1)-ori_im_center_x) * cosd(adjustAngle) - (ROI_rect_ori(2)-ori_im_center_y) * sind(adjustAngle) );
            tempORI(2) = round( rot_im_center_y + (ROI_rect_ori(2)-ori_im_center_y) * cosd(adjustAngle) + (ROI_rect_ori(1)-ori_im_center_x) * sind(adjustAngle) );

            tempORI(3) = round( rot_im_center_x + (ROI_rect_ori(1)+ ROI_width -ori_im_center_x) * cosd(adjustAngle) - (ROI_rect_ori(2)+ ROI_height-ori_im_center_y) * sind(adjustAngle) );
            tempORI(4) = round( rot_im_center_y + (ROI_rect_ori(2)+ ROI_height-ori_im_center_y) * cosd(adjustAngle) + (ROI_rect_ori(1)+ ROI_width -ori_im_center_x) * sind(adjustAngle) );

            ROI_rect_ori(1) = round(( tempORI(1) + tempORI(3) ) / 2 - ROI_width  / 2);  
            ROI_rect_ori(2) = round(( tempORI(2) + tempORI(4) ) / 2 - ROI_height / 2);
        end
        
        % 顯示目前 ROI 內容
        fh = figure(7);
        imshow(ROI, 'border', 'tight', 'initialmagnification', 'fit');  
        set(fh,'Position',[1463,135,size(ROI,2)*1,size(ROI,1)*1]);
     
        % 存下每一步驟的 ROI 狀態
        %{     
        print( fh, strcat('test sample\car plate dataset\saveas\', num2str(file) ,'\ROI-step', num2str(step), '.eps'), '-depsc' );
        saveas(fh, strcat('test sample\car plate dataset\saveas\', num2str(file) ,'\ROI-step', num2str(step), '.jpg') );
        %}   
        step = step + 1;
    end  % end while
    
    % 驗證以去除誤報 很多狀況未掌握 先不做驗證
    % ROI_validate(ROI); 

    % 把輸出的 ROI 中的每個字元存出
    %{
    CCs = bwconncomp(map,8);
    CCp  = regionprops(CCs);
    
    for i = 1:size(CCp,1)
            character = ones(size(map));
            character(CCs.PixelIdxList{i}) = 0;
            imwrite( character , strcat('test sample\car plate dataset\saveas\characters\', num2str(file), '_', num2str(i) , '.jpg') );
    end
    %}
       
    % 回傳值(最終調整的ROI結果)
    exact_ROI = [ROI2im_x1 ROI2im_y1 ROI2im_x2 ROI2im_y2 ROI2im_x3 ROI2im_y3 ROI2im_x4 ROI2im_y4];

end

