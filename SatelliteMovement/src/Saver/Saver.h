#ifndef SAVER_H
#define SAVER_H

#include "../SatelliteData/SatelliteData.h"
#include "../Vector3/Vector3.h"
#include "../const.h"

#include <memory>
#include <mutex>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Saver {
public:
    Saver(std::string& fileName);
   ~Saver();
    void saveToFile(SatelliteData& data);

private:
    std::ofstream file_;
};

#endif //SAVER_H