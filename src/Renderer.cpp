#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../inc/glm/glm.hpp"
#include "../inc/glm/gtc/matrix_transform.hpp"
#include "../inc/glm/gtc/type_ptr.hpp"
#include "../inc/checkGLError.hpp"
#include "../inc/Renderer.hpp"
#include "../inc/Shader.hpp"

const GLuint WIDTH = 1080, HEIGHT = 720;
GLFWwindow* window = nullptr;
GLuint cubeVAO, cubeVBO, cubeEBO;


const float cubeV[] = {    
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f
};

const unsigned int cubeI[] = {
    0, 1, 2,
    2, 3, 0,
    4, 5, 6,
    6, 7, 4,
    8, 9, 10,
    10, 11, 8,
    12, 13, 14,
    14, 15, 12,
    16, 17, 18,
    18, 19, 16,
    20, 21, 22,
    22, 23, 20
};

void setupCube()
{
    CHECK_GL_ERROR(glGenVertexArrays(1, &cubeVAO));
    CHECK_GL_ERROR(glGenBuffers(1, &cubeVBO));
    CHECK_GL_ERROR(glGenBuffers(1, &cubeEBO));

    CHECK_GL_ERROR(glBindVertexArray(cubeVAO));

    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, cubeVBO));
    CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, sizeof(cubeV), cubeV, GL_STATIC_DRAW));

    CHECK_GL_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO));
    CHECK_GL_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeI), cubeI, GL_STATIC_DRAW));

    CHECK_GL_ERROR(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));
    CHECK_GL_ERROR(glEnableVertexAttribArray(0));

    CHECK_GL_ERROR(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));
    CHECK_GL_ERROR(glEnableVertexAttribArray(1));

    CHECK_GL_ERROR(glBindVertexArray(0));
}

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

    setupCube();
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

void drawCube() {
    CHECK_GL_ERROR(glBindVertexArray(cubeVAO));
    CHECK_GL_ERROR(glDrawArrays(GL_TRIANGLES, 0, 36));
    CHECK_GL_ERROR(glBindVertexArray(0));
}


void setupCamera(Shader &shader)
{
    if (!shader.program) {
        std::cerr << "Shader program not initialized" << std::endl;
        exit(1);
    }

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(
    glm::vec3(0.0f, 0.0f, 15.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f));

    GLint modelLoc = glGetUniformLocation(shader.program, "model");
    GLint viewLoc = glGetUniformLocation(shader.program, "view");
    GLint projectionLoc = glGetUniformLocation(shader.program, "projection");

    if(modelLoc == -1  || viewLoc == -1 || projectionLoc == -1) {
        std::cerr << "Failed to get uniform location" << std::endl;
        exit(1); 

    }

    CHECK_GL_ERROR(glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)));
    CHECK_GL_ERROR(glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view)));
    CHECK_GL_ERROR(glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection)));
}