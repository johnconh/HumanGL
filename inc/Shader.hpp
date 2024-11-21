#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include "glm/glm.hpp"

class Shader {
    public:
        GLuint program;

        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        void setMatrix4(const std::string &name, const glm::mat4 &matrix) const;
        void use();

    private:
        std::string readFile(const std::string& filePath);
        void checkCompileErrors(GLuint shader, std::string type);
};

#endif
