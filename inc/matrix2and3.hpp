#pragma once

#include <array>
#include <cmath>

class Matrix2
{
    public:
        std::array<float, 4> data;
        Matrix2();
        Matrix2(const std::array<float, 4>& values);
        Matrix2 operator*(const Matrix2& other) const;
        float& operator[](int index);
        const float& operator[](int index) const;
        float* getPtr();
        const float* getPtr() const;
};


class Matrix3 
{
    public:
        std::array<float, 9> data;
        Matrix3();
        Matrix3(const std::array<float, 9>& values);
        Matrix3 operator*(const Matrix3& other) const;
        float& operator[](int index);
        const float& operator[](int index) const;
        float* getPtr();
        const float*  getPtr() const;
};