fileID = fopen(filename, 'r');

dataMatrix = fread(fileID, [3, inf], 'double');

fclose(fileID);

x = dataMatrix(1, :);
y = dataMatrix(2, :);
z = dataMatrix(3, :);

skip = 111;

fig = figure;
scatter3(x(1:skip:end),y(1:skip:end),z(1:skip:end),30, z(1:skip:end) - min(z(1:skip:end)), 'filled', 'MarkerFaceAlpha',0.2, 'MarkerEdgeAlpha',0.2);
hold on;
xlabel("Distance");
ylabel("Velocity");
zlabel("Acceleration");

%waitfor(fig);