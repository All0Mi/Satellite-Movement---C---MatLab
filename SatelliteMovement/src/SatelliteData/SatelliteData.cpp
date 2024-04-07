#include "SatelliteData.h"

void SatelliteData::genData(Satellite &sat, point &A, point &B) {

    std::vector<double> distance = CalcEngine::biStaticDistance(sat, A, B, numOfTestPoints_);
    std::vector<double> velocity = CalcEngine::biStaticVelocity(sat, A, B, numOfTestPoints_);
    std::vector<double> accel = CalcEngine::biStaticAcceleration(sat, velocity, numOfTestPoints_);

    while (distance.size() > numOfTestPoints_) distance.pop_back();
    while (velocity.size() > numOfTestPoints_) velocity.pop_back();
    while (accel.size() > numOfTestPoints_) accel.pop_back();

    DistanceList_.emplace_back(distance);
    VelocityList_.emplace_back(velocity);
    AccelerationList_.emplace_back(accel);
}

DataPoint SatelliteData::getDataPoint(int n, int m) {
    return {DistanceList_[n][m], VelocityList_[n][m], AccelerationList_[n][m]};
}
