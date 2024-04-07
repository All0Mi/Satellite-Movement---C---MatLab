#include "Plot.h"

void Plot::plotWindows(std::string dir) {
    std::string cmd = "matlab.exe -nosplash -nodesktop -r \"filename=;run('./matlabPlot.m');\"";

    cmd.replace(cmd.find("filename="), sizeof("filename="), "filename=\'" + dir + "\';");

    system(cmd.c_str());
}

void Plot::plotLinux(std::string dir) {
    std::string cmd = "matlab -nosplash -nodesktop -r \"filename=;run('./matlabPlot.m');\"";

    cmd.replace(cmd.find("filename="), sizeof("filename="), "filename=\'" + dir + "\';");

    system(cmd.c_str());
}

void Plot::plotData(std::string dir) {
#if __linux__
    plotLinux(dir);
#elif _WIN32
    plotWindows(dir);
#endif
}
