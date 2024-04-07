#ifndef VECTOR3_H
#define VECTOR3_H

#include <array>
#include <ostream>
#include <cmath>

template<int M, int S>
class Vector3 {
public:
    Vector3() : Vector3(0,0,0){}

    Vector3(double x, double y, double z)
            : v_({x, y, z}){};

    Vector3& operator=(const Vector3& other) {
        if (this != &other) {
            v_ = other.v_;
        }
        return *this;
    }

    bool operator==(const Vector3& other) const {
        return v_[0] == other[0] && v_[1] == other[1] && v_[2] == other[2];
    }

    bool operator<(double other) const {
        return v_[0] < other && v_[1] < other && v_[2] < other;
    }

        Vector3 operator+(const Vector3& other) {
        return Vector3(v_[0] + other.v_[0], v_[1] + other.v_[1], v_[2] + other.v_[2]);
    }

    Vector3 operator-(const Vector3& other) {
        return Vector3(v_[0] - other.v_[0], v_[1] - other.v_[1], v_[2] - other.v_[2]);
    }

    Vector3 operator/(double scalar) {
        return Vector3(v_[0] / scalar, v_[1] / scalar, v_[2] / scalar);
    }

    double& operator[](int index) {
        return v_.at(index);
    }

    const double& operator[](int index) const {
        return v_.at(index);
    }

    Vector3 operator*(const Vector3& other) const { //vector * vector
        return Vector3(v_[0] * other.v_[0], v_[1] * other.v_[1], v_[2] * other.v_[2]);
    }

    Vector3 operator*(double scalar) const {
        return Vector3(v_[0] * scalar, v_[1] * scalar, v_[2] * scalar);
    }

    static double norm(const Vector3& vec) {
        return std::sqrt(vec.v_[0]*vec.v_[0] + vec.v_[1]*vec.v_[1] + vec.v_[2]*vec.v_[2]);
    }

    static Vector3 crossProduct(const Vector3& A, const Vector3& B) {
        return Vector3<M,S>(A[1]*B[2] -A[2]*B[1],A[2]*B[0]-A[0]*B[2], A[0]*B[1] - A[1] * B[0]);
    }

    static bool areParallel(const Vector3& A, const Vector3& B) {
        return ((std::abs(A[0] * B[1] - A[1] * B[0]) < 0.1) && (std::abs(A[1] * B[2] - A[2] * B[1]) < 0.1));
    }

    Vector3 abs() {
        return Vector3<M,S>(std::abs(v_[0]), std::abs(v_[1]), std::abs(v_[2]));
    }

    // Rodrigues' rotation formula
    static Vector3 rotateAroundAxis(Vector3 point, Vector3 axis, double theta) {
        axis = axis / norm(axis);
        double cosTheta = cos(theta);
        double sinTheta = sin(theta);
        return point*cosTheta + crossProduct(axis, point)*sinTheta + axis*(axis*point)*(1 - cosTheta);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
        os << "" << vec.v_[0] << " " << vec.v_[1] << " " << vec.v_[2] << "";
        return os;
    }


private:
    std::array<double, 3> v_;
};

#endif //VECTOR3_H
