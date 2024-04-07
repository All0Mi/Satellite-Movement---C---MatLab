#ifndef SATELLITEDATA_H
#define SATELLITEDATA_H

#include "../SafeVector/SafeVector.h"
#include "../Satellite/Satellite.h"
#include "../CalcEngine/CalcEngine.h"
#include <mutex>

class SatelliteData {
public:
    SatelliteData(int numOfTestPoints, int numOfSatellites):
    numOfTestPoints_(numOfTestPoints),
    numOfSatellites_(numOfSatellites){};

    void genData(Satellite &sat, point &A, point &B);

    int getSize() { return  numOfTestPoints_; }
    int getCount() { return  numOfSatellites_; }

    DataPoint getDataPoint(int n, int m);

private:
    int numOfSatellites_;
    int numOfTestPoints_;
    SafeVector<std::vector<double>> DistanceList_;
    SafeVector<std::vector<double>> VelocityList_;
    SafeVector<std::vector<double>> AccelerationList_;
};

#endif //SATELLITEDATA_H
