filename = 'data.txt'; % replace with your filename
fileID = fopen(filename, 'r');
formatSpec = '%f,%f,%f';

% Read the file line by line
while ~feof(fileID)
   line = fgetl(fileID);
   C = textscan(line, formatSpec, 'Delimiter', ';');
   plot3(C{1}, C{2}, C{3}, ".");
   hold on;
end

fclose(fileID);