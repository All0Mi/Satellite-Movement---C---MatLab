
function randomPerpendicularVector = randomSatelliteAxis(point)
    
    rng(sum(clock,2),'twister');

    % Normalize the input point to get the direction vector
    directionVector = point / norm(point);
    
    % Generate a random vector
    randomVector = randn(3, 1);
    
    % Make sure the random vector is not parallel to the direction vector
    while abs(randomVector' * directionVector) > 0.99
        randomVector = randn(3, 1);
    end
    
    % Compute the cross product to get a vector perpendicular to the direction vector
    randomPerpendicularVector = cross(directionVector, randomVector);
    
    % Normalize the result
    randomPerpendicularVector = randomPerpendicularVector / norm(randomPerpendicularVector);
end
