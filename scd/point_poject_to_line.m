function [p0] = point_poject_to_line( p1, p2, p3 )
% �D���u�~�@�I������v�ܪ��u����v�I
% Input = (���u�W�I p1, ���u�W�I p2, �u�~�@�I p3)
% Output = ��v�I p0

K_factor = dot( (p3 - p1), (p2 - p1) ) / ...
                ( norm(p2 - p1) * norm(p2 - p1) );
            
p0 = K_factor * (p2 - p1) + p1;

end

