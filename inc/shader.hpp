#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "vector.hpp"
#include "matrix4.hpp"
#include "matrix2and3.hpp"
using namespace std;

class Shader {
    public:
        unsigned int id;
        Shader (const char* vertexPath, const char* fragmentPath);
        void use();
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setVec2(const std::string &name, const Vec2 &value) const;
        void setVec2(const std::string &name, float x, float y) const;
        void setVec3(const std::string &name, const Vec3 &value) const;
        void setVec3(const std::string &name, float x, float y, float z) const;
        void setVec4(const std::string &name, const Vec4 &value) const;
        void setVec4(const std::string &name, float x, float y, float z, float w);
        void setMat2(const std::string &name, const Matrix2 &mat) const;
        void setMat3(const std::string &name, const Matrix3 &mat) const;
        void setMat4(const std::string &name, const Matrix4 &mat) const;
    private:
        void checkCompileErrors(unsigned int shader, std::string type);
};
