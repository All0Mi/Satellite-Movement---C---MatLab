#ifndef CONST_H
#define CONST_H

const double EARTH_RADIUS = 6371;   //km
const double GRAV_CONST = 6.6743e-11;   //m3 kg-1 s-2
const double EARTH_MASS = 5.97219e24;   //kg
const double EARTH_ANG_SPEED = 7.2722E-5;   // rad/s

using point = Vector3<1,0>;
using axis = Vector3<1,0>;
using rVector = Vector3<1,0>;
using vVector = Vector3<1,1>;

struct DataPoint {
    double distance;
    double velocity;
    double acceleration;
};

#endif //CONST_H
