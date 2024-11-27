#include "../inc/shader.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include "../inc/checkGLError.hpp"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexCode = readFile(vertexPath);
    std::string fragmentCode = readFile(fragmentPath);

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    checkCompileErrors(program, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() {
    glUseProgram(program);
}

std::string Shader::readFile(const std::string& filePath) {
    std::ifstream file;
    std::stringstream buffer;

    file.open(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        exit(1);
    }
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}

void Shader::checkCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

void Shader::setMatrix4(const std::string &name, const Matrix4 &matrix) const {
    GLint location = glGetUniformLocation(program, name.c_str());
    if (location == -1) {
        std::cerr << "Failed to get uniform location: " << name << std::endl;
        exit(1);
    }
    CHECK_GL_ERROR(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix.m[0][0]));
}

void Shader::setVector3(const std::string &name, const Vector3 &vector) const {
    GLint location = glGetUniformLocation(program, name.c_str());
    if (location == -1) {
        std::cerr << "Failed to get uniform location: " << name << std::endl;
        exit(1);
    }
    CHECK_GL_ERROR(glUniform3f(location, vector.x, vector.y, vector.z));
}
