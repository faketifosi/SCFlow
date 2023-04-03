function Clusters = optics_clustering( data, im )
% 從 OPTICS 輸出的 reachability plot 分析提出 cluster

global xOrdered;

% invoice 參數設定
%
MinPts = ceil(size(data,1) / 10);  
Ksi = 0.05;
%}

% car plate & banknote 參數設定
%{
MinPts = ceil(size(data,1) / 6);
Ksi = 0.05;
%}

% [reachability distance, core distance, 資料順序]
[RD,CD,order] = optics(data, MinPts);
xOrdered = data(order,:);
% RP: RD 依照順序排列形成 reachability plot
RP = RD(order);

%% Ksi-steep point

UpPoint = [];
DownPoint = [];

for i = 2:numel(RP)-1
    
    if RP(i) <= ( RP(i+1)*(1-Ksi) )
        UpPoint = [UpPoint i];
    elseif ( RP(i)*(1-Ksi) ) >= RP(i+1)
        DownPoint = [DownPoint i];
    end
    
end

% 畫出 reachability plot
%{
figure;
bar(RP);
hold on;
bar(DownPoint,zeros(1,numel(DownPoint))+RP(DownPoint),'c');
bar(UpPoint,zeros(1,numel(UpPoint))+RP(UpPoint),'r');
hold off;
%}

%% Ksi-steep area

UpArea = struct([]);
DownArea = struct([]);
attribute = zeros( [1 numel(RP)] );

% SoA:start of area
% EoA:start of area
SoA = 0; EoA = 0; searching = false;
% downward searching
for i = 2:numel(RP)-1
    
    if ~isempty( find(DownPoint == i) ) && searching == false
        searching = true;
        SoA = i;
        EoA = i;
    elseif ~isempty( find(DownPoint == i) ) && searching == true ...
            && RP(i) <= RP(i-1)
        EoA = i;
    elseif searching == true && (RP(i) > RP(i-1) || i == numel(RP)-1)
        DownArea(numel(DownArea)+1).area = [ SoA EoA ];
        searching = false;
    end
end

SoA = 0; EoA = 0; searching = false;
% upward searching
for i = 2:numel(RP)-1
    
    if searching == true && (RP(i) < RP(i-1) || i == numel(RP)-1)
        UpArea(numel(UpArea)+1).area = [ SoA (EoA+1) ];
        searching = false;
    end
    
    if ~isempty( find(UpPoint == i) ) && searching == false
        searching = true;
        SoA = i;
        EoA = i;
    elseif ~isempty( find(UpPoint == i) ) && searching == true ...
            && RP(i) >= RP(i-1)
        EoA = i;
    end
    
    
end

for i = 1:numel(UpArea)
    attribute( UpArea(i).area(1):UpArea(i).area(2) ) = 1;
end

for i = 1:numel(DownArea)
    attribute( DownArea(i).area(1):DownArea(i).area(2) ) = 2;
end



%% Ksi-steep clusters

SDAset = struct([]);
Clusters = struct([]);
index = 2; mib = 0;

% 依照 paper 提供的分析 RP 取得 cluster 的演算法
while index < numel(RP)
    
    mib = max(mib, RP(index));
    
    if attribute(index) == 2
        
        rejectSeq = [];
        for j = 1:numel(SDAset)
            if RP(SDAset(j).area(1))*(1-Ksi) < mib  
               rejectSeq = [rejectSeq j];
            end
        end
        
        SDAset(rejectSeq) = [];
        
        D = [];
        
        for k = 1:numel(DownArea)
            if DownArea(k).area(1) <= index && DownArea(k).area(end) >= index
                D = DownArea(k).area;
                break;
            end
        end
        
        DsetIdx = numel(SDAset)+1;
        SDAset(DsetIdx).area = D;
        SDAset(DsetIdx).mib = max( RP((D(1)+1):D(end)) );
        index = D(end) + 1; mib = RP(index);
        
    elseif attribute(index) == 1

        rejectSeq = [];
        for j = 1:numel(SDAset)
            if RP(SDAset(j).area(1))*(1-Ksi) < mib  
               rejectSeq = [rejectSeq j];
            end
        end
        
        SDAset(rejectSeq) = [];
        
        U = [];
        
        for k = 1:numel(UpArea)
            if UpArea(k).area(1) <= index && UpArea(k).area(end) >= index
                U = UpArea(k).area;
                break;
            end
        end
         
        for j = 1:numel(SDAset)
            if SDAset(j).mib <= RP(U(end))*(1-Ksi)
                Clusters(numel(Clusters)+1).element = [SDAset(j).area(1) U(end)];
            else
                for k = SDAset(j).area(1) : SDAset(j).area(2)
                    if RP(k) - RP(U(end)) <= RP(k)*(Ksi)
                        Clusters(numel(Clusters)+1).element = [k-1 U(end)];
                    end
                end
            end        
        end
        
        if U(end) >= numel(RP)
            break;
        end
        
        index = U(end) + 1; mib = RP(index);
        
    else
        
        % 在車牌應用使用，某些 sample 能夠成功被處理
        %{
        % add for car plate
        if index == numel(RP)-1
            for j = 1:numel(SDAset)
                Clusters(numel(Clusters)+1).element = [SDAset(j).area(1) index];
            end
        end
        %}
        
        index = index + 1;
    end
    
end

% 條件限制
rejectSeq = [];
for j = 1:numel(Clusters)
    
    sD = Clusters(j).element(1);   % cluster start point
    eU = Clusters(j).element(end); % cluster end point
    
    iter = 0;
    while( iter < 1 && eU < numel(RP) )  % 滿足條件 4)
                 
        if RP( sD )*(1-Ksi) >= RP( eU + 0)  
            while RP( sD ) > RP( eU + 0) 
                sD = sD + 1;
            end
            sD = sD - 1;
        elseif RP( sD ) <= RP( eU + 0 )*(1-Ksi) 
            while RP( eU + 0 ) > RP( sD ) 
                eU = eU - 1;
            end
            eU = eU + 1;
        else
            break;
        end
        
        iter = iter + 1;   
    end
    
    distance_mean = mean(RP(sD + 1:eU - 1));
    
    % 邊邊若大過裡面平均距離到某個程度就往內縮
    while RP( eU - 1 ) > 3*distance_mean || RP(eU) > RP(sD)
    	eU = eU - 1;
    end
    
    while RP( sD + 1 ) > 3*distance_mean 
    	sD = sD + 1;
    end
    
    if isempty( find( RP(sD + 1:eU - 1) > 3*distance_mean ) )
        Clusters(j).element = [sD eU];
    else
        rejectSeq = [rejectSeq j];
    end
    
end

% 把不符合限制的 cluster 移除
Clusters(rejectSeq) = [ ];

% 相互包含則取大者，相互交叉則合併
rejectSeq = [];
for j = 1:numel(Clusters)
    for k = j:numel(Clusters)
        
        if ( ( Clusters(j).element(1) >= Clusters(k).element(1) && Clusters(j).element(1) <= Clusters(k).element(2) )   || ...
             ( Clusters(j).element(2) >= Clusters(k).element(1) && Clusters(j).element(2) <= Clusters(k).element(2) )   || ...
             ( Clusters(k).element(2) >= Clusters(j).element(1) && Clusters(k).element(2) <= Clusters(j).element(2) )   || ...
             ( Clusters(k).element(2) >= Clusters(j).element(1) && Clusters(k).element(2) <= Clusters(j).element(2) ) ) && ...
                    k ~= j
            if Clusters(j).element(2) - Clusters(j).element(1) > Clusters(k).element(2) - Clusters(k).element(1)
                Clusters(j).element = [ min(Clusters(j).element(1), Clusters(k).element(1)) max(Clusters(j).element(2), Clusters(k).element(2)) ];
                rejectSeq = [rejectSeq k];
            else
                Clusters(k).element = [ min(Clusters(j).element(1), Clusters(k).element(1)) max(Clusters(j).element(2), Clusters(k).element(2)) ];
                rejectSeq = [rejectSeq j];
            end
        end
        
    end
end

% 把不符合限制的 cluster 移除
Clusters(rejectSeq) = [ ];

% add for car plate
% 完全沒有形成 cluster 如果第一個 reachability distance 小於某個值，則將所有點設為一個 clust r
%{
if ~numel(Clusters) 
    if  RD(1) < 200 
        Clusters(1).element = [1 numel(RP)];
    end
end
%}

end
