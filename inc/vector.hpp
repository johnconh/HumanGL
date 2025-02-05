#pragma once

#include <array>
#include <cmath>
#include <algorithm>
#include "../inc/glm/glm.hpp"

class Vec2
{
    public:
        std::array<float, 2> data;
        Vec2();
        Vec2(float x, float y);

        float& operator[](int index);
        const float& operator[](int index) const;

        float& x();
        float& y();
        const float& x() const;
        const float& y() const;
};

class Vec3
{
    public:
        std::array<float, 3> data;
        Vec3();
        Vec3(float x, float y, float z);

        float& operator[](int index);
        const float& operator[](int index) const;
        float& x();
        float& y();
        float& z();
        const float& x() const;
        const float& y() const;
        const float& z() const; 

        Vec3 operator+(const Vec3& other) const;
        Vec3 operator += (const Vec3& other);
        Vec3 operator-(const Vec3& other) const;
        Vec3 operator-= (const Vec3& other);
        Vec3 operator*(float scalar) const;
        Vec3 operator*=(float scalar);
        Vec3 operator/(float scalar) const;
        Vec3 operator/=(float scalar);

        float length() const;
        Vec3 normalize() const;
        static Vec3 normalize(const Vec3& vec);
        static Vec3 cross(const Vec3& a, const Vec3& b);
        float dot (const Vec3& other) const;
        static float dot(const Vec3& a, const Vec3& b);
        static Vec3 mix(const Vec3& start, const Vec3& end, float factor);
        void fromGLM(const glm::vec3& glmVec);
};

class Vec4
{
    public:
        std::array<float, 4> data;
        Vec4();
        Vec4(float x, float y, float z, float w);

        float& operator[](int index);
        const float& operator[](int index) const;

        float& x();
        float& y();
        float& z();
        float& w();
        const float& x() const;
        const float& y() const;
        const float& z() const;
        const float& w() const;
};