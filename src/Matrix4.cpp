#include "../inc/matrix4.hpp"

Matrix4::Matrix4() {
    *this = identity();
}

Matrix4::Matrix4(const std::array<float, 16>& values) : data(values) {}

Matrix4 Matrix4::operator*(const Matrix4& other) const {
    std::array<float, 16> result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float sum = 0.0f;
            for (int k = 0; k < 4; k++) {
                sum += data[i * 4 + k] * other.data[k * 4 + j];
            }
            result[i * 4 + j] = sum;
        }
    }
    return Matrix4(result);
}

float& Matrix4::operator[](int index) {
    return data[index];
}

const float& Matrix4::operator[](int index) const {
    return data[index];
}

Matrix4 Matrix4::identity(){
    std::array<float, 16> id = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    return Matrix4(id);
}

Matrix4 Matrix4::perspective(float fov, float aspect, float near, float far) {
    Matrix4 result;
    float tanHalfFov = std::tan(fov * PI / 360.0f);

    result[0] = 1.0f / (aspect * tanHalfFov);
    result[5] = 1.0f / tanHalfFov;
    result[10] = (far + near) / (near - far);
    result[11] = -1.0f;
    result[14] = (2.0f * far * near) / (near - far);
    result[15] = 0.0f;

    return result;
}

Matrix4 Matrix4::translate(float x, float y, float z) {
    Matrix4 result = identity();
    result[12] = x;
    result[13] = y;
    result[14] = z;

    return result;
}

Matrix4 Matrix4::scale(float x, float y, float z) {
    Matrix4 result = identity();
    result[0] = x;
    result[5] = y;
    result[10] = z;

    return result;
}

Matrix4 Matrix4::rotate(float angle, float x, float y, float z) {
    Matrix4 result = identity();

    float rad = angle * PI / 180.0f;
    float c = std::cos(rad);
    float s = std::sin(rad);
    float omc = 1.0f - c;

    float length = std::sqrt(x * x + y * y + z * z);
    if(length != 1.0f){
        x /= length;
        y /= length;
        z /= length;
    }

    result[0] = x * x * omc + c;
    result[1] = y * x * omc + z * s;
    result[2] = x * z * omc - y * s;

    result[4] = x * y * omc - z * s;
    result[5] = y * y * omc + c;
    result[6] = y * z * omc + x * s;

    result[8] = x * z * omc + y * s;
    result[9] = y * z * omc - x * s;
    result[10] = z * z * omc + c;

    return result;
}