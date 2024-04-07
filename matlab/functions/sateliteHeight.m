function height = sateliteHeight(point,radius)
    point_norm = point/norm(point);
    height = norm(point - point_norm .* radius);
end

