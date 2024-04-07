#include "Saver.h"

Saver::Saver(std::string &fileName) : file_(fileName, std::ios::trunc | std::ios::binary) {}

Saver::~Saver() { file_.close(); }

void Saver::saveToFile(SatelliteData &data) {
    uint32_t binaryMarker = 0xFFFFFFFF;
    for(int n = 0; n < data.getCount(); n++){
        for (int i = 0; i < data.getSize(); i++){
            DataPoint dp = data.getDataPoint(n, i);
            file_.write(reinterpret_cast<char*>(&dp), sizeof(DataPoint));
        }
        //file_.write(reinterpret_cast<char*>(&binaryMarker), sizeof(binaryMarker));
    }
}
