#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <mutex>
#include <thread>
#include <vector>
#include <functional>

#include "../RandomGenerator/RandomGenerator.h"
#include "../SatRange/SatRange.h"
#include "../Vector3/Vector3.h"
#include "../SafeVector/SafeVector.h"
#include "../const.h"
#include "../Threads/Thread.h"

class Initializer {
public:
    static std::vector<point> generateSetOfValidPoints(int numOfPoints, int numOfThreads, point A, point B) {
        RandomGenerator gen;

        double Rmin = EARTH_RADIUS + 200;
        double Rmax = EARTH_RADIUS + 2000;

        std::array<double, 4> planeA = SatRange::perpendicularPlane(A);
        std::array<double, 4> planeB = SatRange::perpendicularPlane(B);

        SafeVector<point> points;

        auto worker = [&](int start, int end) {
            for (int i = start; i < end; ++i) {
                point randPoint = gen.randValidPoint(Rmin, Rmax);

                if(SatRange::planeFactor(randPoint, planeA) < planeA[3]) continue;
                if(SatRange::planeFactor(randPoint, planeB) < planeB[3]) continue;

                points.emplace_back(randPoint);
            }
        };

        Threads::runThreads(numOfPoints, numOfThreads, worker);

        return points.get();
    }

    static std::vector<Satellite> initSatellites(std::vector<point> &points, point A, point B, int numOfThreads) {
        std::vector<Satellite> satellites;

        for (auto & point : points) {
            satellites.emplace_back(point);
        }

        auto worker = [&](int start, int end) {
            for (int i = start; i < end; ++i) {
                satellites[i].setRange(SatRange::findRange(satellites[i], A, B, 14));
            }
        };

        Threads::runThreads(satellites.size(), numOfThreads, worker);

        return satellites;
    }
};

#endif //INITIALIZER_H