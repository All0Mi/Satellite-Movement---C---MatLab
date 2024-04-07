#include "Simulator.h"
#include "../Threads/Thread.h"

void Simulator::start(int randSatellitePoints, point A, point B, int numOfTestPoints, int numOfThreads, std::string filePath) {
    std::vector<point> validPoints = Initializer::generateSetOfValidPoints(randSatellitePoints, numOfThreads, A, B);
    std::vector<Satellite> satellites = Initializer::initSatellites(validPoints, A, B, numOfThreads);

    SatelliteData satData(numOfTestPoints, satellites.size());

    auto worker = [&](int start, int end) {
        for (int i = start; i < end; i++) {
            satData.genData(satellites[i], A, B);
        }
    };

    Threads::runThreads(satellites.size(), numOfThreads, worker);

    exportData(filePath, satData);

}

void Simulator::exportData(std::string &filePath, SatelliteData &data) {
    Saver saver(filePath);
    saver.saveToFile(data);
}
