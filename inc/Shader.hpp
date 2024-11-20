#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader {
    public:
        GLuint program;

        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        void use();

    private:
        std::string readFile(const std::string& filePath);
        void checkCompileErrors(GLuint shader, std::string type);
};

#endif
