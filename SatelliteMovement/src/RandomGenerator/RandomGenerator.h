#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include "../Vector3/Vector3.h"
#include "../const.h"

#include <random>
#include <cmath>

class RandomGenerator {
public:
    RandomGenerator() : engine_(device_()){}

    double randDouble() {
        return randDouble(0,1);
    }

    double randInt() {
        return randInt(0,1);
    }

    double randDouble(double min, double max) {
        std::uniform_real_distribution<double> dist(min,max);
        return dist(engine_);
    }

    double randInt(int min, int max) {
        std::uniform_int_distribution<int> dist(min,max);
        return dist(engine_);
    }

    rVector randValidPoint(double Rmin, double Rmax) {

        double newMaxRange;
        double newMinRange;

        rVector point;
        std::array<rVector, 8> multipliers = {rVector(1, 1,1),      //We only generate positive numbers, so multiplying them by random
                                              rVector(-1, 1,1),     //vector from multipliers will evenly distribute points between
                                              rVector(1, -1,1),     //positive and negative
                                              rVector(-1, -1,1),
                                              rVector(1, 1,-1),
                                              rVector(-1, 1,-1),
                                              rVector(1, -1,-1),
                                              rVector(-1, -1,-1)};

        point[0] = randDouble(0, Rmax);     //first number can be random between 0 and max

        newMaxRange = sqrt((Rmax * Rmax) - (point[0] * point[0]));         //we reduce upper limit, so the norm won't pass Rmax after getting next value

        point[1] = randDouble(0, newMaxRange);        //Second number gets range calculated earlier

        newMaxRange = sqrt((Rmax * Rmax) - (point[0] * point[0]) - (point[1] * point[1]));    //Calculating new max

        if (rVector::norm(point) < Rmin) {                                      //If numbers got ealier are too smal, we set lower limit so norm from all three numbers will be no lower than min
            newMinRange = sqrt((Rmin*Rmin)-(point[1] * point[1]) - (point[0] * point[0]));
        } else {
            newMinRange = 0;
        }

        point[2] = randDouble(newMinRange, newMaxRange);

        point = point * multipliers[randInt(0, 7)];     //At the end we multiply our point by random vector from multipliers array, so we get negative values

        return point;
    }


private:
    std::random_device device_;
    std::default_random_engine engine_;
};

#endif //RANDOMGENERATOR_H
