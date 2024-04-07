#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "../SatelliteData/SatelliteData.h"
#include "../Initializer/Initializer.h"
#include "../CalcEngine/CalcEngine.h"
#include "../Vector3/Vector3.h"
#include "../Saver/Saver.h"
#include "../const.h"

#include <functional>
#include <string>

class Simulator {
public:
    Simulator()= default;
    void start(int randSatellitePoints, point A, point B, int numOfTestPoints, int numOfThreads, std::string filePath);

private:
    static void exportData(std::string& filePath, SatelliteData& data);
};
#endif //SIMULATOR_H
