function [ exact_ROI ] = ROI_extract( im, candidate_ROI, SIFT_point )
% ���P�� ROI �����禡
% candidate_ROI = (x1,y1,x2,y2,x3,y3,x4,y4);

step = 1; % �º�O�����N����

global ROI_property;
global number_of_object;
global file;

% mkdir( strcat('test sample\car plate dataset\saveas\', num2str(file) ) );
% �إ߻P�ɮ׽s���ۦP���s�ɥؿ�

    % �Y�p�d��A�u�d�U�Կ�ϰ����d��
    middleX = round(( candidate_ROI(5) + candidate_ROI(1) ) / 2);
    middleY = round(( candidate_ROI(4) + candidate_ROI(2) ) / 2); 
    plate = [middleX-100 middleY-50 middleX+100 middleY+50];
    % plate = [ �����X�y�� �W���Y�y�� �k���X�y�� �U���Y�y�� ]
    
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
        
 
    
    % ���j���զ�s�q����(���i�ର���P)�@�]���鵲�G�y�t�A�w�]�����ĥ�
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
 
    % �q�C���o���ӥդ��i�ର�r��������
    im_temp(im_temp > 100) = 255;
    % �j���զ⪫�骺�d��A�Ω�z��X�i�ର���P����
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


    totalRotAngle = 0;      %�֭p��eROI�����`�@�����ਤ��

    im_center_x = size(im,2) / 2;   %�ؼмv�����y�Ф���
    im_center_y = size(im,1) / 2;

       
    theta = 0; % ���P�}�l������A�e���X��
    rot_im = imrotate(im,theta,'bilinear','loose');     %��J�v���̷Ӫ즸ROI���ױ���H�K�s���ާ@

    
    rot_im_ori = imrotate(im_ori,theta,'bilinear','loose');

    rot_im_center_x = size(rot_im,2) / 2;   % ����L��v������
    rot_im_center_y = size(rot_im,1) / 2;

    theta = -theta;
    totalRotAngle = totalRotAngle + theta;
    
    % ����L�᪺ROI�|�ӳ��I
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
       
    % ��e ROI �����I.���e��T
    ROI_rect_ori = round([UL_X UL_Y]);
    ROI_width  = round( ((candidate_ROI(1) - candidate_ROI(5))^2 + (candidate_ROI(2) - candidate_ROI(6))^2 )^0.5 );
    ROI_height = round( ((candidate_ROI(1) - candidate_ROI(3))^2 + (candidate_ROI(2) - candidate_ROI(4))^2 )^0.5 );
   
    % �@�}�l�� ROI �Y�L�p�h�y�L�[�j
    if ROI_width < 10 
        ROI_width = ROI_width + 10;
    end
    
    if ROI_height < 10 
        ROI_height = ROI_height + 10;
    end
    
    iterative = true;   % ����N�~��P�_���X��
    chance = true;  % "�Ӧ��������ѵ��G�h�����@�����|"������X��
    shifted = false;    % ����s�򲾰ʪ�����X��
    right_adjust = false;   % �j��k���ʱ���X��
    left_adjust = false;    % �j������ʱ���X��
    fit = false;    % �Ω�����K�X��e ROI ���e������X��
    rotated = false;    % ����s��⦸���N������B�z������X��
    rotate_count = 0;   % �֭p����ե����ƥH���L��ɳB�z������X��
    
    % �i�J���N fit ROI �{��
    while iterative
        
        iterative = false;
        
        fh = figure(3);
        imshow(im, 'border', 'tight', 'initialmagnification', 'fit');
        set (fh,'Position',[805,600,640,360]);
        hold on;
        
        % �p�⦹�r���N�� ROI ����Ϫ��|���I�y�Ц�m
        ROI2im_x1 = round( im_center_x + (ROI_rect_ori(1)-rot_im_center_x) * cosd(-totalRotAngle) - (ROI_rect_ori(2)-rot_im_center_y) * sind(-totalRotAngle) );
        ROI2im_y1 = round( im_center_y + (ROI_rect_ori(2)-rot_im_center_y) * cosd(-totalRotAngle) + (ROI_rect_ori(1)-rot_im_center_x) * sind(-totalRotAngle) );

        ROI2im_x2 = round( im_center_x + (ROI_rect_ori(1)+ROI_width-rot_im_center_x) * cosd(-totalRotAngle) - (ROI_rect_ori(2)-rot_im_center_y) * sind(-totalRotAngle) );
        ROI2im_y2 = round( im_center_y + (ROI_rect_ori(2)-rot_im_center_y) * cosd(-totalRotAngle) + (ROI_rect_ori(1)+ROI_width-rot_im_center_x) * sind(-totalRotAngle) );

        ROI2im_x3 = round( im_center_x + (ROI_rect_ori(1)-rot_im_center_x) * cosd(-totalRotAngle) - (ROI_rect_ori(2)+ROI_height-rot_im_center_y) * sind(-totalRotAngle) );
        ROI2im_y3 = round( im_center_y + (ROI_rect_ori(2)+ROI_height-rot_im_center_y) * cosd(-totalRotAngle) + (ROI_rect_ori(1)-rot_im_center_x) * sind(-totalRotAngle) );

        ROI2im_x4 = round( im_center_x + (ROI_rect_ori(1)+ROI_width-rot_im_center_x) * cosd(-totalRotAngle) - (ROI_rect_ori(2)+ROI_height-rot_im_center_y) * sind(-totalRotAngle) );
        ROI2im_y4 = round( im_center_y + (ROI_rect_ori(2)+ROI_height-rot_im_center_y) * cosd(-totalRotAngle) + (ROI_rect_ori(1)+ROI_width-rot_im_center_x) * sind(-totalRotAngle) );

        % ��ܥثe ROI �b��l�v���W���ϰ�
        line([ROI2im_x1 ROI2im_x2],[ROI2im_y1 ROI2im_y2],'Color', 'c','LineWidth',2);
        line([ROI2im_x2 ROI2im_x4],[ROI2im_y2 ROI2im_y4],'Color', 'c','LineWidth',2);
        line([ROI2im_x1 ROI2im_x3],[ROI2im_y1 ROI2im_y3],'Color', 'c','LineWidth',2);
        line([ROI2im_x4 ROI2im_x3],[ROI2im_y4 ROI2im_y3],'Color', 'c','LineWidth',2);
        hold off;
        
        %������ɡA�YROI���վ�W�X�v���d��h�������X(�ȮɨS�B�z, ����i��i, �ثe���X�h��������)
        if ROI2im_x1 < 1 || ROI2im_x1 > size(im,2) || ROI2im_x2 < 1 || ROI2im_x2 > size(im,2) || ROI2im_x3 < 1 || ...
                ROI2im_x3 > size(im,2) || ROI2im_x4 < 1 || ROI2im_x4 > size(im,2) || ROI2im_y1 < 1 || ROI2im_y1 > size(im,1) || ...
                ROI2im_y2 < 1 || ROI2im_y2 > size(im,1) || ROI2im_y3 < 1 || ROI2im_y3 > size(im,1) || ROI2im_y4 < 1 || ROI2im_y4 > size(im,1)
            exact_ROI = [ROI2im_x1 ROI2im_y1 ROI2im_x2 ROI2im_y2 ROI2im_x3 ROI2im_y3 ROI2im_x4 ROI2im_y4];
            return;
        end
        
        % �s�X�Y�ӭ��N���q�b��v������ROI���A
        %{
        print( fh, strcat('test sample\car plate dataset\saveas\', num2str(file) ,'\ori-step', num2str(step), '.eps'), '-depsc' );
        saveas(fh, strcat('test sample\car plate dataset\saveas\', num2str(file) ,'\ori-step', num2str(step), '.jpg') );
        %}      
        
        % �b����᪺�v���W��ܥثe���o�� ROI
        fh = figure(4);
        imshow(rot_im_ori, 'border', 'tight', 'initialmagnification', 'fit');
        set (fh,'Position',[805,135,640,360]);
        hold on;
        line([ROI_rect_ori(1) ROI_rect_ori(1)+ROI_width],[ROI_rect_ori(2) ROI_rect_ori(2)],'Color', 'c','LineWidth',2);
        line([ROI_rect_ori(1) ROI_rect_ori(1)],[ROI_rect_ori(2) ROI_rect_ori(2)+ROI_height],'Color', 'c','LineWidth',2);
        line([ROI_rect_ori(1)+ROI_width ROI_rect_ori(1)+ROI_width],[ROI_rect_ori(2) ROI_rect_ori(2)+ROI_height],'Color', 'c','LineWidth',2);
        line([ROI_rect_ori(1) ROI_rect_ori(1)+ROI_width],[ROI_rect_ori(2)+ROI_height ROI_rect_ori(2)+ROI_height],'Color', 'c','LineWidth',2);
        hold off;
        
        % �s�X�Y�ӭ��N���q�b�����v������ROI���A
        %{        
        print( fh, strcat('test sample\car plate dataset\saveas\', num2str(file) ,'\rot-step', num2str(step), '.eps'), '-depsc' );
        saveas(fh, strcat('test sample\car plate dataset\saveas\', num2str(file) ,'\rot-step', num2str(step), '.jpg') );
        %}
        
        % �q�����v�������X ROI pixel ���e
        ROI_rect_ori = round(ROI_rect_ori);
        ROI = rot_im( [ROI_rect_ori(2):(ROI_rect_ori(2)+ROI_height)], [ROI_rect_ori(1):(ROI_rect_ori(1)+ROI_width)] );
        
        % image enhancement
        H = fspecial('gaussian');
        ROI = imfilter(ROI,H,'replicate');
        ROI = imadjust(ROI);
        H = fspecial('unsharp');
        ROI = imfilter(ROI,H,'replicate');
        % end of image enhancement

        % �u����edge���ϰ찵�G�Ȥ�
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
        
        % ��]�t�Ҧ� edge ���̤p�ϰ찵����
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
        
        % �ӱ����ROI�v����ɴN��^��ɭȡA�_�h�ĪG���n
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
        
        %�@Otsu �G�Ȥ�
        BW_ROI(top:bottom,left:right) = ROI(top:bottom,left:right);
        BW_ROI = im2bw(BW_ROI, graythresh( ROI(find(map==128)) ));
                      
        BW_ROI = 1 - BW_ROI;
        % connected component labeling
        CCs = bwconncomp(BW_ROI,8);
        CCp  = regionprops(CCs);
        
        % ROI �G�ȤƤ���S���󤺮e�������X
        if size(CCp,1) < 1
            exact_ROI = 0;
            return;
        end
        
        % �������T ���e��Τj�p�P���e�t�Ӧh�h�L�o
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
        
        % �p�� edge pixel ��������v
        for i = 1:size(edge_image,2)
            edge_hist(i) = sum(edge_image(:,i));
        end
                     
        %{ 
        ��l�Ƴ̤j component �ܼ� (�@������ ROI���z��.�X�i.����.���� ���Ѧҥؼ�)
        maxAreaCC = 0;    maxArea = 0;   
        % ���o���n�̤j�� component
        for i = 1:size(CCp,1)
            area = CCp(i).BoundingBox(3) * CCp(i).BoundingBox(4);
            if area > maxArea
                maxArea = area;
                maxAreaCC = i;
            end
        end
        %}
        
        % �M�� median area component
        CC_tempSeq = zeros(size(CCp,1),1);
        for i = 1:size(CCp,1)
            CC_tempSeq(i) = [CCp(i).BoundingBox(3) * CCp(i).BoundingBox(4)];
        end
        
        % �p�⭱�n�A���� component
        [CC_sortByArea index] = sort(CC_tempSeq);
        maxAreaCC = index( floor(size(index,1)/2) + 1 );
        maxArea = CC_tempSeq(maxAreaCC);
        
        % �������n�̤j�� component
        maxAreaCC_struct = CCp(maxAreaCC);
        
        % ��l map �ܼƦ����¼v��
        map = zeros(size(ROI));
                
        quantity = 0;    % number of character ("�ثe"���q��ROI���������`��) 
        skewErrTop = 0; skewErrBot = 0;     % �ֿn�ɱ׻~�t

        % �H�̤j���n component ���Ѧҿz��j�p�L�p�� component
        % �íp��U�O component ���̤j component ���W�U���ײ֭p�~�t, �����������ध��
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
        
        % ROI�������P������v
        hor_hist = zeros( size(BW_ROI,1),1 );
        for i = 1:size(BW_ROI,1)
            hor_hist(i) = sum( BW_ROI(i,:) );
        end
        
        ver_hist = zeros( 1,size(BW_ROI,2) );
        for i = 1:size(BW_ROI,2)
            ver_hist(i) = sum( BW_ROI(:,i) );
        end
           
        % ��ܤG�Ȥƨÿz��᪺�v��
        fh = figure(5);
        imshow(map, 'border', 'tight', 'initialmagnification', 'fit');   
        set(fh,'Position',[1463,600, size(map,2)*2.5, size(map,1)*2.5]);   
        
        % ��ܤG�Ȥƨÿz��᪺�v��
        %{        
        print( fh, strcat('test sample\car plate dataset\saveas\', num2str(file) ,'\map-step', num2str(step), '.eps'), '-depsc' );
        saveas(fh, strcat('test sample\car plate dataset\saveas\', num2str(file) ,'\map-step', num2str(step), '.jpg') );
        %}      

       %% false positive elimination�@�]ROI���A�P�Ѧҹ�H��ҶW�X�e�\�d��h����^
        if (size(ROI,2) / maxAreaCC_struct.BoundingBox(3) > ROI_property.ROI_to_CCs_ratio.widthRatio * 3.5) ...           % 2.5
                || (size(ROI,1) / maxAreaCC_struct.BoundingBox(4) > ROI_property.ROI_to_CCs_ratio.heightRatio * 5) ...    % 3 or 4 
                || (( size(ROI,2) / size(ROI,1) ) > ROI_property.aspect_ratio * 1.5) && (size(ROI,1)*size(ROI,2) > 500)
            break;
        end
                 
       %% rotate
        % �֭p�~�t�j��̤j component �����׬Y�ӵ{�קY����
        if skewErrTop >= maxAreaCC_struct.BoundingBox(4)*0.5 && skewErrBot >= maxAreaCC_struct.BoundingBox(4)*0.5 && ~rotated && rotate_count < 10 %����ƤW��
            
            maxAreaCC = 0;    maxArea = 0;
        
            for i = 1:size(CCp,1)
                area = CCp(i).BoundingBox(3) * CCp(i).BoundingBox(4);
                if area > maxArea
                    maxAreaCC = i;
                    maxArea = area;
                end
            end
                                 
            if maxAreaCC > 1    % �קK�W�X�s�������� (�H�̤j���n component ���󬰰�ǩ����Ѧ�)
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
            
            if adjustAngle ~= 0 %�Y�������ਤ�������A�h����ó]�w���N
            
                iterative = true;
                                          
                adjustAngle = -adjustAngle;
                totalRotAngle = totalRotAngle + adjustAngle;
                
                rot_im = imrotate(im, -totalRotAngle,'bilinear','loose');   % ����ե�

                ori_im_center_x = rot_im_center_x;   % ����e�v������
                ori_im_center_y = rot_im_center_y;

                rot_im_center_x = size(rot_im,2) / 2;   % �����v������
                rot_im_center_y = size(rot_im,1) / 2; 

                tempORI(1) = round( rot_im_center_x + (ROI_rect_ori(1)-ori_im_center_x) * cosd(adjustAngle) - (ROI_rect_ori(2)-ori_im_center_y) * sind(adjustAngle) );
                tempORI(2) = round( rot_im_center_y + (ROI_rect_ori(2)-ori_im_center_y) * cosd(adjustAngle) + (ROI_rect_ori(1)-ori_im_center_x) * sind(adjustAngle) );

                tempORI(3) = round( rot_im_center_x + (ROI_rect_ori(1)+ ROI_width -ori_im_center_x) * cosd(adjustAngle) - (ROI_rect_ori(2)+ ROI_height-ori_im_center_y) * sind(adjustAngle) );
                tempORI(4) = round( rot_im_center_y + (ROI_rect_ori(2)+ ROI_height-ori_im_center_y) * cosd(adjustAngle) + (ROI_rect_ori(1)+ ROI_width -ori_im_center_x) * sind(adjustAngle) );

                % ����� ROI ���e
                ROI_rect_ori(1) = round(( tempORI(1) + tempORI(3) ) / 2 - ROI_width  / 2);   % ��e ROI ��T
                ROI_rect_ori(2) = round(( tempORI(2) + tempORI(4) ) / 2 - ROI_height / 2);

                fit = true;  % �����վ� ROI �ܪA�K��r
                rotated = true;  % ����s�����⦸���X��   
                
                continue;    
            end
            
        end
        
        % ����s�����⦸
        if rotated == true
            rotated = false;
        end
        
        % �֥[���স�ơA�W�L�]�w�ȫh����N
        rotate_count = rotate_count + 1;
        % end rotate                            

       %% expand. shift            
        
        % add for car (�Ѧ�edge���������i�β��ʡA���N��G�ȤƼv������v)
        ver_hist = edge_hist;
       
        if quantity < number_of_object % component �p��8�� �V���ΦV�k�X�i
            
            % �q map �Ҽ{���k�Ŷ�
            map_CC_margin = [ ceil(CCp(1).BoundingBox(1)) - 1 size(map,2) - ceil(CCp(end).BoundingBox(1)+CCp(end).BoundingBox(3)) ];
                               
            % �q��l ROI �Ҽ{���k�Ŷ�
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
                       
            if shifted   % ���s�� shift �⦸, ���M�Φ��L���j��(���ФϦV����)
                shifted = false;
            end
            
            % �ץ��k�� (�Y�@��ťճB�Ӧh���ϦV���ʭץ�)
            if map_CC_margin(1) > size(map,2)/3 && ~iterative && ~right_adjust
                
                if ROI2im_x1 + ROI_width + map_CC_margin(1) <= size(im,2)
                    ROI_rect_ori(1) = ROI_rect_ori(1) + map_CC_margin(1);
                    iterative = true;
                    shifted = true;
                    right_adjust = true;
                end                                   
            % �ץ�����
            elseif map_CC_margin(2) > size(map,2)/3 && ~iterative && ~left_adjust
                ROI_rect_ori(1) = ROI_rect_ori(1) - map_CC_margin(2);
                
                if ROI_rect_ori(1) <= 0
                    ROI_rect_ori(1) = 1;
                end
                
                iterative = true;
                shifted = true;
                left_adjust = true;
            end
            
            % ���k�첾 (�������e���վ㤧����h�Ѧҭ�l�v�����ⰼ�ťճB����)
            if left_margin >= maxAreaCC_struct.BoundingBox(3) && left_margin > right_margin*2 && ~iterative && shifted
                
                if ROI_rect_ori(1) + ROI_width + maxAreaCC_struct.BoundingBox(3) <= size(im,2)
                    ROI_rect_ori(1) = ROI_rect_ori(1) + maxAreaCC_struct.BoundingBox(3);
                    iterative = true;
                    shifted = true;
                end   
            % �����첾
            elseif right_margin >= maxAreaCC_struct.BoundingBox(3) && right_margin > left_margin*2 && ~iterative && shifted
                ROI_rect_ori(1) = ROI_rect_ori(1) - maxAreaCC_struct.BoundingBox(3);
                
                if ROI_rect_ori(1) <= 0
                    ROI_rect_ori(1) = 1;
                end
                
                iterative = true;
                shifted = true;
            end
          
            % ���k���i�A�ѦҤG�ȤƨùL�o���T�᪺�v��������v���� �P �S�x�I�Ͷ� ��ܩ��@��V�X�i ROI �j�p                    
            if right_margin <= ( 1.5*maxAreaCC_struct.BoundingBox(3) ) && right_expand && ~iterative || (left_margin >= right_margin && ~left_expand)
                offset = size(im,2) - (ROI2im_x1 + ROI_width); % ����X�v�����(���~�t,�S�B�z�ܦn)
                
                if ROI2im_x1 + ROI_width + round( 0.5*maxAreaCC_struct.BoundingBox(3) ) > size(im,2)
                    ROI_width = ROI_width + abs(offset);
                else
                    ROI_width = ROI_width + round( 0.5*maxAreaCC_struct.BoundingBox(3) );
                end
                
                if offset~=0
                    iterative = true;
                end
            % �������i
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
        
        % ��������ťճB�K�X�ثe�Ҧ� ROI ���e
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
            if sum( map(size(map,1), :) ) > 0   % �U��ɥ]�t component �V�U���i
                ROI_height = ROI_height + 2;
                iterative = true;
            end

            if sum( map(1, :) ) > 0     % �W��ɥ]�t component �V�W���i
                ROI_rect_ori(2) = ROI_rect_ori(2) - 2;
                ROI_height = ROI_height + 2;
                iterative = true;
            end

            if sum( map(:, 1) ) > 0     % ����ɥ]�t component �V�����i
                ROI_rect_ori(1) = ROI_rect_ori(1) - 2;
                ROI_width = ROI_width + 2;
                iterative = true;
            end

            if sum( map(:, size(map,2)) ) > 0    % �k��ɥ]�t component �V�k���i
                ROI_width = ROI_width + 2;
                iterative = true;
            end            
        end

        % end if expand. shift
        
        % give some chance (���S�ب�F���� 90 ��)
        if size(CCp,1) < 3 && chance && ~iterative
            chance = false;
            iterative = true;
                          
            adjustAngle = -90;
            rot_im = imrotate(rot_im,adjustAngle,'bilinear','loose');   % ����ե�

            ori_im_center_x = rot_im_center_x;   % ����e�v������
            ori_im_center_y = rot_im_center_y;

            rot_im_center_x = size(rot_im,2) / 2;   % �����v������
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
        
        % ��ܥثe ROI ���e
        fh = figure(7);
        imshow(ROI, 'border', 'tight', 'initialmagnification', 'fit');  
        set(fh,'Position',[1463,135,size(ROI,2)*1,size(ROI,1)*1]);
     
        % �s�U�C�@�B�J�� ROI ���A
        %{     
        print( fh, strcat('test sample\car plate dataset\saveas\', num2str(file) ,'\ROI-step', num2str(step), '.eps'), '-depsc' );
        saveas(fh, strcat('test sample\car plate dataset\saveas\', num2str(file) ,'\ROI-step', num2str(step), '.jpg') );
        %}   
        step = step + 1;
    end  % end while
    
    % ���ҥH�h���~�� �ܦh���p���x�� ����������
    % ROI_validate(ROI); 

    % ���X�� ROI �����C�Ӧr���s�X
    %{
    CCs = bwconncomp(map,8);
    CCp  = regionprops(CCs);
    
    for i = 1:size(CCp,1)
            character = ones(size(map));
            character(CCs.PixelIdxList{i}) = 0;
            imwrite( character , strcat('test sample\car plate dataset\saveas\characters\', num2str(file), '_', num2str(i) , '.jpg') );
    end
    %}
       
    % �^�ǭ�(�̲׽վ㪺ROI���G)
    exact_ROI = [ROI2im_x1 ROI2im_y1 ROI2im_x2 ROI2im_y2 ROI2im_x3 ROI2im_y3 ROI2im_x4 ROI2im_y4];

end

