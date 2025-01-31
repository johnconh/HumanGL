#include "../inc/matrix2and3.hpp"

Matrix2::Matrix2() : data({
    1.0f, 0.0f, 
    0.0f, 1.0f}) {}
Matrix2::Matrix2(const std::array<float, 4>& values) : data(values) {}
Matrix2 Matrix2::operator*(const Matrix2& other) const {
    std::array<float, 4> result;
    result[0] = data[0] * other.data[0] + data[1] * other.data[2];
    result[1] = data[0] * other.data[1] + data[1] * other.data[3];
    result[2] = data[2] * other.data[0] + data[3] * other.data[2];
    result[3] = data[2] * other.data[1] + data[3] * other.data[3];
    return Matrix2(result);
}
float& Matrix2::operator[](int index) {return data[index];}
const float& Matrix2::operator[](int index) const {return data[index];}
float* Matrix2::getPtr() {return data.data();}
const float* Matrix2::getPtr() const {return data.data();}

//==================================================================================================

Matrix3::Matrix3() : data({
    1.0f, 0.0f, 0.0f, 
    0.0f, 1.0f, 0.0f, 
    0.0f, 0.0f, 1.0f}) {}
Matrix3::Matrix3(const std::array<float, 9>& values) : data(values) {}
Matrix3 Matrix3::operator*(const Matrix3& other) const {
    std::array<float, 9> result;
    result[0] = data[0] * other.data[0] + data[1] * other.data[3] + data[2] * other.data[6];
    result[1] = data[0] * other.data[1] + data[1] * other.data[4] + data[2] * other.data[7];
    result[2] = data[0] * other.data[2] + data[1] * other.data[5] + data[2] * other.data[8];
    result[3] = data[3] * other.data[0] + data[4] * other.data[3] + data[5] * other.data[6];
    result[4] = data[3] * other.data[1] + data[4] * other.data[4] + data[5] * other.data[7];
    result[5] = data[3] * other.data[2] + data[4] * other.data[5] + data[5] * other.data[8];
    result[6] = data[6] * other.data[0] + data[7] * other.data[3] + data[8] * other.data[6];
    result[7] = data[6] * other.data[1] + data[7] * other.data[4] + data[8] * other.data[7];
    result[8] = data[6] * other.data[2] + data[7] * other.data[5] + data[8] * other.data[8];
    return Matrix3(result);
}
float& Matrix3::operator[](int index) {return data[index];}
const float& Matrix3::operator[](int index) const {return data[index];}
float* Matrix3::getPtr() {return data.data();}
const float* Matrix3::getPtr() const {return data.data();}
