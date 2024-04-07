#ifndef SATELLITE_H
#define SATELLITE_H

#include <ctime>

#include "../RandomGenerator/RandomGenerator.h"
#include "../Vector3/Vector3.h"
#include "../const.h"

class Satellite {
public:
    Satellite(point point) : point_(point), height_(height(point)), speed_(speed(height_)),
                                axis_(randomRotationAxis(point)), range_({0,0}) {}

    point getPoint() const { return point_; }

    axis getAxis() const { return axis_; }

    double getHeight() const { return height_; }

    double getSpeed() const { return speed_; }

    double getVelocity() const { return speed_ * (height_ + EARTH_RADIUS);}

    std::array<int,2> getRange() {return range_; }

    void setRange(std::array<int,2> range) {range_ = range;}
    void setAxis(axis v) {axis_ = v;}

    static axis randomRotationAxis(point point) {

        RandomGenerator gen{};

        rVector DirectionVector = point / point::norm(point);
        rVector RandomVector(gen.randDouble(),gen.randDouble(),gen.randDouble());

        while (rVector::areParallel(DirectionVector, RandomVector)) {
            RandomVector = rVector(gen.randDouble(),gen.randDouble(),gen.randDouble());
        }

        axis RandomPerpendicularVector = rVector::crossProduct(RandomVector, DirectionVector);
        RandomPerpendicularVector = RandomPerpendicularVector / axis::norm(RandomPerpendicularVector);

        return RandomPerpendicularVector;
    }



private:
    point point_;
    double height_;
    double speed_;
    axis axis_;
    std::array<int,2> range_;

    double speed(double height) {
        double speed = sqrt((GRAV_CONST * EARTH_MASS) / ((EARTH_RADIUS + height) * 1000)) / 1000;
        return speed / (EARTH_RADIUS + height);
    }

    double height(point point) {
        rVector pointNorm = point / point::norm(point);
        return rVector::norm(point - pointNorm * EARTH_RADIUS);
    }

};


#endif //SATELLITE_H
