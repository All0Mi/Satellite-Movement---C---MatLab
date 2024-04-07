clear all;
addpath("./functions/");
addpath("./constants/");
addpath("./class/");
const = const;
rng(sum(clock,2),'twister');

% RX/TX Positions 
pointA = [3690; 1340; 5017];
pointB = [3658; -421; 5199];

% In ECEF Z axis is roataion axis
EarthAxisOfRoataion = [0; 0; 1]; 

n_testpoints = 500;

% Min and Max radius of orbit for satelite (LEO)
Rmin = const.earthRadius + 200;
Rmax = const.earthRadius + 2000;

% Coefficients (Ax+By+Cz=D) of the planes perpendicular to the points
planeA = perpendicularPlane(pointA);
planeB = perpendicularPlane(pointB);

planeFactor = @(plane, point) plane(1) * point(1) + plane(2) * point(2) + plane(3) * point(3);
X = [];
Y = [];
Z = [];

% Generate random points
fprintf("Generating random points\n");
for i = 1:1:100000
    x(i) = random(-Rmax, Rmax);
    y(i) = random(-Rmax, Rmax);
    z(i) = random(-Rmax, Rmax);

   % Check if the point is: 
   % a) at the right altitude, 
   % b) within radar range,
   % and add it to list of correct points
   if (norm([x(i),y(i),z(i)]) <= Rmax && norm([x(i),y(i),z(i)]) >= Rmin)
       if(~(planeFactor(planeA, [x(i), y(i), z(i)]) > planeA(4))) continue, end
       if(~(planeFactor(planeB, [x(i), y(i), z(i)]) > planeB(4))) continue, end 
        X = [X, x(i)];
        Y = [Y, y(i)];
        Z = [Z, z(i)];
   end
end


% Number of qualified points
n = size(X,2);
fprintf("Generated %d valid satelites\n", n);

% Initialization of the list of satellite objects
fprintf("Initialization of satellites list\n");
for i = 1:1:n
    point = [X(i);Y(i);Z(i)];                           % Pos vector
    height = sateliteHeight(point, const.earthRadius);  % Altitude/Height
    sat_axis = randomSatelliteAxis(point);              % Random rotation axis
    speed = orbitalSpeed(height);                       % Angular speed
    Satelites(i) = Satelite(point, sat_axis, speed);
end

% Find rotation range of satelite for random orbit (start*speed or end*speed) 
fprintf("Searching for the range of valid satellite positions\n");
for i = 1:1:n
    [start, stop] = findRange(Satelites(i), pointA, pointB, const);
    Satelites(i).start = start;
    Satelites(i).stop = stop;
end


for i = 1:n
    % Read sat data from the object
    sat = Satelites(i).pos;
    sat_axis = Satelites(i).axis;
    speed = Satelites(i).speed;
    start = Satelites(i).start;
    stop = Satelites(i).stop;
    step = (abs(start) + abs(stop))/(n_testpoints-1);
    radius = Satelites(i).radius;


    fprintf("Working on satelite: %d\n", i);

    % Init arrays
    r = [];
    v = [];
    a = [];

    % Calculate bistatic distance (for each valid position)
    for j = stop:step:start+step
        pos = rotateAroundAxis(sat, sat_axis, j * speed);               % Sat roation
        A = rotateAroundAxis(pointA, [0 0 1], const.EarthAngSpeed*j);   % Earth rotation
        B = rotateAroundAxis(pointB, [0 0 1], const.EarthAngSpeed*j);   % Earth rotation
        r = [r, norm(pos-A) + norm(pos-B)];

        r1 = pos - A;
        r2 = pos - B;

        V = cross(sat_axis, sat);
        V = V/norm(V) * speed * 3.6 * radius;
        
        v = [v, (r1/norm(r1)+r2/norm(r2))' * V];
    end

    % Calculate accelerations
    for j = 2:1:n_testpoints+step
        a = [a, (v(j)-v(j-1))/step];
    end

    % Save caluclated values for later
    distance(i, :) = r;
    velocity(i, :) = v;
    accel(i, :) = a;

end

%%% Plots
figure;

subplot(1,3,1);
for i = 1:5
    plot(velocity(i, 1:n_testpoints));
    hold on;
end
title('Velocity');

subplot(1,3,2);
for i = 1:5
    plot(distance(i, 1:n_testpoints));
    hold on;
end
title('Dsitance');

subplot(1,3,3);
for i = 1:5
    plot(accel(i, 1:n_testpoints));
    hold on;
end
title('Accel');


figure;
for n = 1:25
    col = [rand rand rand];
    for i = 1:n_testpoints
        plot3(velocity(n, i), distance(n, i), accel(n, i), '.', 'Color', col);
        hold on;
    end
end
xlabel('Velovity');
ylabel('Distance');
zlabel('Acceleration');


figure;
plot3(X,Y,Z, 'r.');
hold on;

[X,Y,Z] = sphere;
axis equal;
surf(X*const.earthRadius, Y*const.earthRadius, Z*const.earthRadius);

f = @(x,y) (planeA(4) - planeA(1)*x - planeA(2)*y)/planeA(3);
fsurf(f, [pointA(1)-const.earthRadius, pointA(1)+const.earthRadius, pointA(2)-const.earthRadius, pointA(2)+const.earthRadius])

f = @(x,y) (planeB(4) - planeB(1)*x - planeB(2)*y)/planeB(3);
fsurf(f, [pointB(1)-const.earthRadius, pointB(1)+const.earthRadius, pointB(2)-const.earthRadius, pointB(2)+const.earthRadius])
