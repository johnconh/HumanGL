#include "../inc/renderer.hpp"

const GLuint WIDTH = 1080, HEIGHT = 720;
GLFWwindow* window = nullptr;

void initRenderer() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Tutorial", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(1);
    }
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);

    if (version) {
        std::cout << "OpenGL version: " << version << std::endl;
        std::cout << "Renderer: " << renderer << std::endl;
        std::cout << "Vendor: " << vendor << std::endl;
    } else {
        std::cerr << "Error getting OpenGL version" << std::endl;
    }

}

void clearScreen() {
    CHECK_GL_ERROR(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    CHECK_GL_ERROR(glEnable(GL_DEPTH_TEST));
    CHECK_GL_ERROR(glDepthFunc(GL_LESS));
}

void swapBuffers() {
    CHECK_GL_ERROR(glfwSwapBuffers(window));
    CHECK_GL_ERROR(glfwPollEvents());
}

void cleanupRenderer() {
    CHECK_GL_ERROR(glfwDestroyWindow(window));
    CHECK_GL_ERROR(glfwTerminate());
}

