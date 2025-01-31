#pragma once

#include <array>
#include <cmath>

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
        const float*  getPtr() const {return data.data();}
    private:
        static constexpr float PI = 3.14159265358979323846f; 
};

