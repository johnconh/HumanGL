#include "../inc/vector.hpp"

//Vector 2
Vec2::Vec2() : data({0.0f, 0.0f}) {}
Vec2::Vec2(float x, float y) : data({x, y}) {}
float& Vec2::operator[](int index) {return data[index];}
const float& Vec2::operator[](int index) const {return data[index];}
float& Vec2::x() {return data[0];}
float& Vec2::y() {return data[1];}
const float& Vec2::x() const {return data[0];}
const float& Vec2::y() const {return data[1];}
// ============================================ //

//Vector 3
Vec3::Vec3() : data({0.0f, 0.0f, 0.0f}) {}
Vec3::Vec3(float x, float y, float z) : data({x, y, z}) {}
float& Vec3::operator[](int index) {return data[index];}
const float& Vec3::operator[](int index) const {return data[index];}
float& Vec3::x() {return data[0];}
float& Vec3::y() {return data[1];}
float& Vec3::z() {return data[2];}
const float& Vec3::x() const {return data[0];}
const float& Vec3::y() const {return data[1];}
const float& Vec3::z() const {return data[2];}

Vec3 Vec3::operator+(const Vec3& other) const {
    return Vec3(data[0] + other.data[0], data[1] + other.data[1], data[2] + other.data[2]);
}
Vec3 Vec3::operator+=(const Vec3& other) {
    data[0] += other.data[0];
    data[1] += other.data[1];
    data[2] += other.data[2];
    return *this;
}
Vec3 Vec3::operator-(const Vec3& other) const {
    return Vec3(data[0] - other.data[0], data[1] - other.data[1], data[2] - other.data[2]);
}
Vec3 Vec3::operator-=(const Vec3& other) {
    data[0] -= other.data[0];
    data[1] -= other.data[1];
    data[2] -= other.data[2];
    return *this;
}
Vec3 Vec3::operator*(float scalar) const {
    return Vec3(data[0] * scalar, data[1] * scalar, data[2] * scalar);
}
Vec3 Vec3::operator*= (float scalar) {
    data[0] *= scalar;
    data[1] *= scalar;
    data[2] *= scalar;
    return *this;
}
Vec3 Vec3::operator/(float scalar) const {
    return Vec3(data[0] / scalar, data[1] / scalar, data[2] / scalar);
}
Vec3 Vec3::operator/=(float scalar) {
    data[0] /= scalar;
    data[1] /= scalar;
    data[2] /= scalar;
    return *this;
}
float Vec3::length() const {
    return std::sqrt(data[0] * data[0] + data[1] * data[1] + data[2] * data[2]);
}
Vec3 Vec3::normalize() const {
    float len = length();
    return Vec3(data[0] / len, data[1] / len, data[2] / len);
}
Vec3 Vec3::normalize(const Vec3& vec) {
    return vec.normalize();
}
Vec3 Vec3::cross(const Vec3& a, const Vec3& b) {
    return Vec3(a.data[1] * b.data[2] - a.data[2] * b.data[1],
                a.data[2] * b.data[0] - a.data[0] * b.data[2],
                a.data[0] * b.data[1] - a.data[1] * b.data[0]);
}
float Vec3::dot(const Vec3& a, const Vec3& b) {
    return a.data[0] * b.data[0] + a.data[1] * b.data[1] + a.data[2] * b.data[2];
}
float Vec3::dot(const Vec3& other) const {
    return data[0] * other.data[0] + data[1] * other.data[1] + data[2] * other.data[2];
}
// ========================================================================================= //

//Vector 4
Vec4::Vec4() : data({0.0f, 0.0f, 0.0f, 0.0f}) {}
Vec4::Vec4(float x, float y, float z, float w) : data({x, y, z, w}) {}
float& Vec4::operator[](int index) {return data[index];}
const float& Vec4::operator[](int index) const {return data[index];}
float& Vec4::x() {return data[0];}
float& Vec4::y() {return data[1];}
float& Vec4::z() {return data[2];}
float& Vec4::w() {return data[3];}
const float& Vec4::x() const {return data[0];}
const float& Vec4::y() const {return data[1];}
const float& Vec4::z() const {return data[2];}
const float& Vec4::w() const {return data[3];}

