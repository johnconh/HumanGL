#include "../inc/matrixStack.hpp"

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3 Vector3::operator+(const Vector3& v) const {
    return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(const Vector3& v) const {
    return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator*(float s) const {
    return Vector3(x * s, y * s, z * s);
}

Vector3 normalize(const Vector3& v) {
    float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return Vector3(v.x / length, v.y / length, v.z / length);
}

Vector3 cross(const Vector3& v, const Vector3& w) {
    return Vector3(v.y * w.z - v.z * w.y, v.z * w.x - v.x * w.z, v.x * w.y - v.y * w.x);
}

float dot(const Vector3& a, const Vector3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 sub(const Vector3& a, const Vector3& b) {
    return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Matrix4::Matrix4() {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(i == j) m[i][j] = 1.0f;
            else m[i][j] = 0.0f;
        }
    }
}

Matrix4 Matrix4::operator*(const Matrix4& matrix) const {
    Matrix4 result;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            result.m[i][j] = 0.0f;
            for(int k = 0; k < 4; k++) {
                result.m[i][j] += m[i][k] * matrix.m[k][j];
            }
        }
    }
    return result;
}

void Matrix4::translate(const Vector3& v) {
    Matrix4 translation;
    translation.m[3][0] = v.x;
    translation.m[3][1] = v.y;
    translation.m[3][2] = v.z;
    *this = *this * translation;
}

void Matrix4::scale(const Vector3& s) {
    Matrix4 scaleMatrix;
    scaleMatrix.m[0][0] = s.x;
    scaleMatrix.m[1][1] = s.y;
    scaleMatrix.m[2][2] = s.z;
    *this = *this * scaleMatrix;
}

void Matrix4::rotateX(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    Matrix4 rotation;
    memset(rotation.m, 0, sizeof(rotation.m));
    rotation.m[0][0] = 1.0f;
    rotation.m[1][1] = c;
    rotation.m[1][2] = -s;
    rotation.m[2][1] = s;
    rotation.m[2][2] = c;
    rotation.m[3][3] = 1.0f;
    *this = *this * rotation;
}

void Matrix4::rotateY(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    Matrix4 rotation;
    memset(rotation.m, 0, sizeof(rotation.m));
    rotation.m[0][0] = c;
    rotation.m[0][2] = s;
    rotation.m[1][1] = 1.0f;
    rotation.m[2][0] = -s;
    rotation.m[2][2] = c;
    rotation.m[3][3] = 1.0f;
    *this = *this * rotation;
}

void Matrix4::rotateZ(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    Matrix4 rotation;
    memset(rotation.m, 0, sizeof(rotation.m));
    rotation.m[0][0] = c;
    rotation.m[0][1] = -s;
    rotation.m[1][0] = s;
    rotation.m[1][1] = c;
    rotation.m[2][2] = 1.0f;
    rotation.m[3][3] = 1.0f;
    *this = *this * rotation;
}

MatrixStack::MatrixStack() {
    stack.push_back(Matrix4());
}

void MatrixStack::push() {
    stack.push_back(top());
}

void MatrixStack::pop() {
    stack.pop_back();
}

Matrix4& MatrixStack::top() {
    return stack.back();
}

void MatrixStack::translate(const Vector3& translation) {
    top().translate(translation);
}

void MatrixStack::scale(const Vector3& scale) {
    top().scale(scale);
}

void MatrixStack::multiply(const Matrix4 &matrix){
    top() = top() * matrix;
}

void MatrixStack::rotateX(float angle){
    top().rotateX(angle);
}

void MatrixStack::rotateY(float angle){
    top().rotateY(angle);
}

void MatrixStack::rotateZ(float angle){
    top().rotateZ(angle);
}

Matrix4 perspective(float fovY, float aspect, float near, float far) {
    float f = 1.0f / std::tan(fovY / 2.0f);
    Matrix4 m;
    std::memset(m.m, 0, sizeof(m.m));
    m.m[0][0] = f / aspect;
    m.m[1][1] = f;
    m.m[2][2] = (far + near) / (near - far);
    m.m[2][3] = -1.0f;
    m.m[3][2] = (2.0f * far * near) / (near - far);
    return m;
}

Matrix4 lookAt(const Vector3& eye, const Vector3& center, const Vector3& up) {
    Vector3 f = normalize(sub(center, eye));
    Vector3 s = normalize(cross(f, up));
    Vector3 u = cross(s, f);
    Matrix4 m;
    std::memset(m.m, 0, sizeof(m.m));
    m.m[0][0] = s.x;
    m.m[0][1] = s.y;
    m.m[0][2] = s.z;
    m.m[1][0] = u.x;
    m.m[1][1] = u.y;
    m.m[1][2] = u.z;
    m.m[2][0] = -f.x;
    m.m[2][1] = -f.y;
    m.m[2][2] = -f.z;
    m.m[3][0] = -dot(s, eye);
    m.m[3][1] = -dot(u, eye);
    m.m[3][2] = dot(f, eye);
    m.m[3][3] = 1.0f;
    return m;
}

void MatrixStack::applyMatrix(const Matrix4& matrix) {
    top() = matrix;
}

float radians(float degrees) {
    return degrees * PI / 180.0f;
}