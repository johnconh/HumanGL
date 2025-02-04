#pragma once
#include <algorithm>
#include <iostream>
#include "matrix4.hpp"

class Quaternion {
    public:
        std::array<float, 4> data;
        Quaternion();
        Quaternion(float x, float y, float z, float w);
        float& w();
        float& x();
        float& y();
        float& z();
        const float& w() const;
        const float& x() const;
        const float& y() const;
        const float& z() const;
        Quaternion operator*(float scalar) const;
        Quaternion operator*(const Quaternion& q) const;
        Quaternion operator+(const Quaternion& other) const;
        Quaternion operator-() const;
        Matrix4 toMatrix() const;
        static Quaternion slerp(const Quaternion& q1, const Quaternion& q2, float factor);
        float dot(const Quaternion& other) const;
        Quaternion normalize() const;
        friend std::ostream& operator<<(std::ostream& os, const Quaternion& q);
};