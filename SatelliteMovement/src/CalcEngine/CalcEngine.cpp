#include "CalcEngine.h"

std::vector<double> CalcEngine::biStaticDistance(Satellite &sat, point &A, point &B, int &numberOfTestPoints) {
    int start = sat.getRange()[0];
    int stop = sat.getRange()[1];
    double step = (double)(abs(start) + abs(stop))/numberOfTestPoints;

    std::vector<double> biStaticDistance;

    for(double i = start; i <= stop + step; i+=step){
        point satPos = point::rotateAroundAxis(sat.getPoint(), sat.getAxis(), sat.getSpeed()*i);
        point PosA = point::rotateAroundAxis(A, rVector(0,0,1), EARTH_ANG_SPEED*i);
        point PosB = point::rotateAroundAxis(B, rVector(0,0,1), EARTH_ANG_SPEED*i);

        biStaticDistance.emplace_back(rVector::norm(satPos - PosA) + rVector::norm(satPos - PosB));
    }

    return biStaticDistance;
}

std::vector<double> CalcEngine::biStaticVelocity(Satellite &sat, point &A, point &B, int &numberOfTestPoints) {
    int start = sat.getRange()[0];
    int stop = sat.getRange()[1];
    double step = (double)(abs(start) + abs(stop)) / numberOfTestPoints;

    std::vector<double> biStaticVelocity;

    for(double i = start; i <= stop + step; i+=step){
        point satPos = point::rotateAroundAxis(sat.getPoint(), sat.getAxis(), sat.getSpeed()*i);
        point PosA = point::rotateAroundAxis(A, rVector(0,0,1), EARTH_ANG_SPEED*i);
        point PosB = point::rotateAroundAxis(B, rVector(0,0,1), EARTH_ANG_SPEED*i);

        rVector r1 = satPos - PosA;
        rVector r2 = satPos - PosB;

        vVector v = crossProduct(satPos, sat.getAxis());
        v = v/vVector::norm(v) * sat.getVelocity();

        rVector normR = r1/rVector::norm(r1) + r2/rVector::norm(r2);

        biStaticVelocity.emplace_back(normR[0]*v[0] + normR[1]*v[1] + normR[2]*v[2]);
    }

    return biStaticVelocity;
}

std::vector<double> CalcEngine::biStaticAcceleration(Satellite &sat, const std::vector<double> &velocity, int &numberOfTestPoints) {
    int start = sat.getRange()[0];
    int stop = sat.getRange()[1];
    double step = (double)(abs(start) + abs(stop)) / numberOfTestPoints;

    std::vector<double> biStaticAcceleration;
    for (auto i = 1; i < velocity.size(); ++i) {
        biStaticAcceleration.emplace_back((velocity[i] - velocity[i-1])/step);
    }

    return biStaticAcceleration;
}

vVector CalcEngine::crossProduct(point point, axis axis){
    return vVector(point[1] * axis[2] - point[2] * axis[1], point[2] * axis[0] - point[0] * axis[2], point[0] * axis[1] - point[1] * axis[0]);
}
