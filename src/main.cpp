#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../inc/checkGLError.hpp"

int main() {
    if (!glfwInit()) {
        std::cerr << "Error al inicializar GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL HumanGL", nullptr, nullptr);
    if (!window) {
        std::cerr << "Error al crear la ventana" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Error al inicializar GLEW" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);

    if (version) {
        std::cout << "Versión de OpenGL: " << version << std::endl;
        std::cout << "Renderer: " << renderer << std::endl;
        std::cout << "Vendor: " << vendor << std::endl;
    } else {
        std::cerr << "Error al obtener la versión de OpenGL" << std::endl;
    }

    while(!glfwWindowShouldClose(window)) {
        CHECK_GL_ERROR(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        CHECK_GL_ERROR(glEnable(GL_DEPTH_TEST));
        CHECK_GL_ERROR(glDepthFunc(GL_LESS));

        
        CHECK_GL_ERROR(glfwSwapBuffers(window));
        CHECK_GL_ERROR(glfwPollEvents());
    }

    CHECK_GL_ERROR(glfwDestroyWindow(window));
    CHECK_GL_ERROR(glfwTerminate());
    return 0;
}
