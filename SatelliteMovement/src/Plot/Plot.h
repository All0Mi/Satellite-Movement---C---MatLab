#ifndef PLOT_H
#define PLOT_H

#include <string>

class Plot {
public:
    static void plotData(std::string dir);
private:
    static void plotLinux(std::string dir);

    static void plotWindows(std::string dir);
};


#endif //PLOT_H
