function plane = perpendicularPlane(point)
    plane = [point(1), point(2), point(3), norm(point)^2];
end