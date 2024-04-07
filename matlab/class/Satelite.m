classdef Satelite
    properties
        pos;
        axis;
        speed;
        start;
        stop;
        radius;
    end
    
    methods
        function obj = Satelite(pos,axis, speed)
            obj.pos = pos;
            obj.speed = speed;
            obj.axis = axis;
            obj.radius = norm(pos);
        end
        
    end
end

