function [start, finish] = findRange(sat, pointA, pointB, const)

    planeFactor = @(plane, point) plane(1) * point(1) + plane(2) * point(2) + plane(3) * point(3);
    
    i = 0;
    while(1)
        sat_point = rotateAroundAxis(sat.pos, sat.axis, sat.speed * i); % Sat rotation
        A = rotateAroundAxis(pointA, [0 0 1], const.EarthAngSpeed*i);   % Earth rotation
        B = rotateAroundAxis(pointB, [0 0 1], const.EarthAngSpeed*i);   % Earth rotation

        planeA = perpendicularPlane(A);
        planeB = perpendicularPlane(B);

        if(planeFactor(planeA, sat_point) < planeA(4) || planeFactor(planeB, sat_point) < planeB(4))
            start = i - 1;
            break;
        end
        i = i + 1;
    end

    i = 0;
    while(1)
        sat_point = rotateAroundAxis(sat.pos, sat.axis, sat.speed * i);
        A = rotateAroundAxis(pointA, [0 0 1], const.EarthAngSpeed*i);
        B = rotateAroundAxis(pointB, [0 0 1], const.EarthAngSpeed*i);

        planeA = perpendicularPlane(A);
        planeB = perpendicularPlane(B);
        
        if(planeFactor(planeA, sat_point) < planeA(4) || planeFactor(planeB, sat_point) < planeB(4))
            finish = i + 1;
            break;
        end
        i = i - 1;
    end
end

