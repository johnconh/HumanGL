#include "../inc/quaternion.hpp"
#include <iostream>

Quaternion::Quaternion(){data = {1.0f, 0.0f, 0.0f, 0.0f};}

Quaternion::Quaternion(float x, float y, float z, float w){data = {x, y, z, w};}

float& Quaternion::w(){return data[0];}
float& Quaternion::x(){return data[1];}
float& Quaternion::y(){return data[2];}
float& Quaternion::z(){return data[3];}
const float& Quaternion::w() const{return data[0];}
const float& Quaternion::x() const{return data[1];}
const float& Quaternion::y() const{return data[2];}
const float& Quaternion::z() const{return data[3];}


Quaternion Quaternion::operator*(float scalar) const {
    return Quaternion(
        data[0] * scalar,
        data[1] * scalar,
        data[2] * scalar,
        data[3] * scalar
    );
}

Quaternion Quaternion::operator*(const Quaternion& q) const {
    return Quaternion(
        w() * q.w() - x() * q.x() - y() * q.y() - z() * q.z(),
        w() * q.x() + x() * q.w() + y() * q.z() - z() * q.y(),
        w() * q.y() - x() * q.z() + y() * q.w() + z() * q.x(),
        w() * q.z() + x() * q.y() - y() * q.x() + z() * q.w()
    ).normalize();
}

Quaternion Quaternion::operator+(const Quaternion& other) const{
    return Quaternion(
        data[0] + other.data[0],
        data[1] + other.data[1],
        data[2] + other.data[2],
        data[3] + other.data[3]
    );
}

Quaternion Quaternion::operator-() const {
    return Quaternion(-data[0], -data[1], -data[2], -data[3]);
}


float Quaternion::dot(const Quaternion& other) const{
    return  data[0] * other.data[0] + 
            data[1] * other.data[1] + 
            data[2] * other.data[2] + 
            data[3] * other.data[3];
}

Quaternion Quaternion::slerp(const Quaternion& q1, const Quaternion& q2, float factor){
    Quaternion start = q1.normalize();
    Quaternion end = q2.normalize();

    float cosTheta = start.dot(end);

    if (cosTheta < 0.0f) {
        end = -end;
        cosTheta = -cosTheta;
    }

    float scale0, scale1;

    if (cosTheta > 0.9999f) {
        scale0 = 1.0f - factor;
        scale1 = factor;
    } else {
        float theta = std::acos(std::clamp(cosTheta, -1.0f, 1.0f));
        float sinTheta = std::sin(theta);

        scale0 = std::sin((1.0f - factor) * theta) / sinTheta;
        scale1 = std::sin(factor * theta) / sinTheta;
    }

    Quaternion result = Quaternion(
        scale0 * start.w() + scale1 * end.w(),
        scale0 * start.x() + scale1 * end.x(),
        scale0 * start.y() + scale1 * end.y(),
        scale0 * start.z() + scale1 * end.z()
    );

    return result.normalize();
}

Quaternion Quaternion::normalize() const{
    float magnitude = std::sqrt(
        data[0] * data[0] + 
        data[1] * data[1] + 
        data[2] * data[2] + 
        data[3] * data[3]
    );

    return  (magnitude > 0) ? Quaternion(
        data[0] / magnitude, 
        data[1] / magnitude, 
        data[2] / magnitude, 
        data[3] / magnitude
    ) : *this;
}

Matrix4 Quaternion::toMatrix() const {
    Quaternion q = normalize();
    
    float x = q.x();
    float y = q.y();
    float z = q.z();
    float w = q.w();
    
    float x2 = x * x;
    float y2 = y * y;
    float z2 = z * z;
    
    return Matrix4({
        1.0f - 2.0f * (y2 + z2),   2.0f * (x * y - w * z),   2.0f * (x * z + w * y),   0.0f,
        2.0f * (x * y + w * z),     1.0f - 2.0f * (x2 + z2), 2.0f * (y * z - w * x),   0.0f,
        2.0f * (x * z - w * y),     2.0f * (y * z + w * x),  1.0f - 2.0f * (x2 + y2),  0.0f,
        0.0f,                       0.0f,                    0.0f,                     1.0f
    });
}

std::ostream& operator<<(std::ostream& os, const Quaternion& q){
    os << "x: " << q.x() << " y: " << q.y() << " z: " << q.z() << " w: " << q.w();
    return os;
}