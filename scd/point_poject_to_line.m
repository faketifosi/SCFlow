function [p0] = point_poject_to_line( p1, p2, p3 )
% 求直線外一點垂直投影至直線的投影點
% Input = (直線上點 p1, 直線上點 p2, 線外一點 p3)
% Output = 投影點 p0

K_factor = dot( (p3 - p1), (p2 - p1) ) / ...
                ( norm(p2 - p1) * norm(p2 - p1) );
            
p0 = K_factor * (p2 - p1) + p1;

end

