#ifndef MATRIXSTACK_HPP
#define MATRIXSTACK_HPP

#include <stack>
#include <vector>
#include <cmath>
#include <cstring>

struct Vector3 {
    float x, y, z;

    Vector3();
    Vector3(float x, float y, float z);
    Vector3 operator+(const Vector3& v) const;
    Vector3 operator-(const Vector3& v) const;
    Vector3 operator*(float s) const;
};

struct Matrix4{
    float m[4][4];

    Matrix4();
    Matrix4 operator*(const Matrix4& matrix) const;
    void translate(const Vector3& translation);
    void scale(const Vector3& scale);
};

class MatrixStack {
    private:
        std::vector<Matrix4> stack;
    public:
        MatrixStack();
        void push();
        void pop();
        Matrix4& top();
        void translate(const Vector3& translation);
        void scale(const Vector3& scale);
};

Vector3 normalize(const Vector3& v);
Vector3 cross(const Vector3& v, const Vector3& w);
float dot(const Vector3& a, const Vector3& b);
Vector3 sub(const Vector3& a, const Vector3& b);
Matrix4 perspective(float fovY, float aspect, float near, float far);
Matrix4 lookAt(const Vector3& eye, const Vector3& target, const Vector3& up);

#endif