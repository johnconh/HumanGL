#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include "matrixStack.hpp"

class Shader {
    public:
        GLuint program;
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        void setMatrix4(const std::string &name, const Matrix4 &matrix) const;
        void setVector3(const std::string &name, const Vector3 &vector) const;
        void use();
    private:
        std::string readFile(const std::string& filePath);
        void checkCompileErrors(GLuint shader, std::string type);
};
#endif