function rotated_point = rotateAroundAxis(point, axis, theta)
    % Normalize the axis vector
    axis = axis / norm(axis);

    % Components of the rotation matrix
    K = [0, -axis(3), axis(2); axis(3), 0, -axis(1); -axis(2), axis(1), 0];
    R = eye(3) + sin(theta) * K + (1 - cos(theta)) * K^2;

    % Apply rotation to the point
    rotated_point = R * point;
end

%  https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula
% 
%  The general rotation matrix is given by the Rodrigues' rotation formula:
%  R = I + sin(a)K + (1-cos(a))K^2
%  Where:
%  I - identity matrix
%  a - rotation angle
%  k - unit vector of rotation axis