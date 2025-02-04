#pragma once

#include <array>
#include <cmath>
#include <iostream>
#include "vector.hpp"


class Matrix4 {
    public:
        std::array<float, 16> data;
        Matrix4();
        Matrix4(const std::array<float, 16>& values);
        Matrix4 operator*(const Matrix4& other) const;
        float& operator[](int index);
        const float& operator[](int index) const;
        static Matrix4 perspective(float fov, float aspect, float near, float far);
        static Matrix4 translate(float x, float y, float z);
        static Matrix4 scale(float x, float y, float z);
        static Matrix4 rotate(float angle, float x, float y, float z);
        static Matrix4 identity();
        static Matrix4 lookAt(const Vec3& eye, const Vec3& center, const Vec3& up);
        const float*  getPtr() const {return data.data();}
        friend std::ostream& operator<<(std::ostream& os, const Matrix4& m);
};  




