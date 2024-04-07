#ifndef CALCENGINE_H
#define CALCENGINE_H

#include <vector>
#include "../Satellite/Satellite.h"
#include "../const.h"

class CalcEngine {
public:
    static std::vector<double> biStaticDistance(Satellite& sat, point& A, point& B,int& numberOfTestPoints);

    static std::vector<double> biStaticVelocity(Satellite& sat, point& A, point& B,int& numberOfTestPoints);

    static std::vector<double> biStaticAcceleration(Satellite& sat, const std::vector<double>& velocity, int& numberOfTestPoints);

    static vVector crossProduct(point point, axis axis);
};

#endif //CALCENGINE_H
