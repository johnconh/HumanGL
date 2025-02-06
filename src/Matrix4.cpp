#include "../inc/matrix4.hpp"

Matrix4::Matrix4() {
    *this = identity();
}

Matrix4::Matrix4(const std::array<float, 16>& values) : data(values) {}

Matrix4 Matrix4::operator*(const Matrix4& other) const {
    std::array<float, 16> result;
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            float sum = 0.0f;
            for (int k = 0; k < 4; k++) {
                sum += data[k * 4 + row] * other.data[col * 4 + k];
            }
            result[col * 4 + row] = sum;
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
    float tanHalfFov = std::tan(fov * M_PI / 360.0f);

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

    float rad = angle * M_PI / 180.0f;
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

Matrix4 Matrix4::lookAt (const Vec3& eye, const Vec3& center, const Vec3& up) {
    Vec3 f = (center - eye).normalize();
    Vec3 s = Vec3::cross(f, up).normalize();
    Vec3 u = Vec3::cross(s, f);

    Matrix4 result = identity();
    
    result[0] = s.x();
    result[1] = u.x();
    result[2] = -f.x();
    result[4] = s.y();
    result[5] = u.y();
    result[6] = -f.y();;
    result[8] = s.z();
    result[9] = u.z();
    result[10] = -f.z();

    result[12] = -s.dot(eye);
    result[13] = -u.dot(eye);
    result[14] = f.dot(eye);

    return result;
}

void Matrix4::fromGLM(const glm::mat4& m) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            data[i * 4 + j] = m[i][j];
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Matrix4& m) {
    os << "[\n";
    for (int i = 0; i < 4; ++i) {
        os << "  ";
        for (int j = 0; j < 4; ++j) {
            os << m.data[i * 4 + j] << " ";
        }
        os << "\n";
    }
    os << "]";
    return os;
}
