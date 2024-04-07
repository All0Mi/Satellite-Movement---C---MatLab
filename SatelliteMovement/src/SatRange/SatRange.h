#ifndef ROTATION_H
#define ROTATION_H
#include "../Satellite/Satellite.h"
#include "../const.h"
#include "cmath"

class SatRange {
public:
    static std::array<int, 2> findRange(Satellite &sat, point &pointA, point &pointB, int numberOfIterations) {
        int start = 0;
        int finish = 0;

        finish = getEnd(sat, pointA, pointB, numberOfIterations);

        start = getStart(sat, pointA, pointB, numberOfIterations);

        return {start, finish};
    }

    static std::array<double, 4> perpendicularPlane(point point) {
        std::array<double, 4> plane = {point[0], point[1], point[2], point::norm(point) * point::norm(point)};
        return plane;
    }

    static long double planeFactor(point& point, std::array<double, 4>& plane) {
        long double PlaneFactor = plane[0] * point[0] + plane[1] * point[1] + plane[2] * point[2];
        return PlaneFactor;
    }

private:
    static bool isSatInRange(Satellite sat, point pointA, point pointB, double i) {
        point SatPoint = point::rotateAroundAxis(sat.getPoint(), sat.getAxis(), sat.getSpeed() * i);
        point rotatedA = point::rotateAroundAxis(pointA, {0,0,1}, EARTH_ANG_SPEED * i );
        point rotatedB = point::rotateAroundAxis(pointB, {0,0,1}, EARTH_ANG_SPEED * i);

        std::array<double, 4> planeA = perpendicularPlane(rotatedA);
        std::array<double, 4> planeB = perpendicularPlane(rotatedB);

        return (planeFactor(SatPoint, planeA) >= planeA[3] && planeFactor(SatPoint, planeB) >= planeB[3]);
    }

    static int getStart(Satellite &sat, point &pointA, point &pointB, int numberOfIterations){
        double halfOfOrbit = M_PI / sat.getSpeed();
        double currentStepSize = halfOfOrbit;
        double currentLocation = -halfOfOrbit;

        for (int i = 1; i <= numberOfIterations; i++) {

            currentStepSize /= 2;

            if (isSatInRange(sat, pointA, pointB, currentLocation)) {
                currentLocation -= currentStepSize;
            } else {
                currentLocation += currentStepSize;
            }
        }

        return int(ceil(currentLocation));
    }

    static int getEnd(Satellite &sat, point &pointA, point &pointB, int numberOfIterations){
        double halfOfOrbit = M_PI / sat.getSpeed();
        double currentStepSize = halfOfOrbit;
        double currentLocation = halfOfOrbit;

        for (int i = 1; i <= numberOfIterations; i++) {

            currentStepSize /= 2;

            if (isSatInRange(sat, pointA, pointB, currentLocation)) {
                currentLocation += currentStepSize;
            } else {
                currentLocation -= currentStepSize;
            }
        }

        return int(floor(currentLocation));
    }
};


#endif //ROTATION_H
