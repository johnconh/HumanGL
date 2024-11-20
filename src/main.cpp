#include "../inc/Shader.hpp"
#include "../inc/Renderer.hpp"
#include "../inc/Model.hpp"
#include "../inc/MatrixStack.hpp"

int main() {

    initRenderer();

    Model humanModel;
    MatrixStack m;
    Shader shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    while(!glfwWindowShouldClose(window)) {
        shader.use();
        clearScreen();
        setupCamera(shader);
        humanModel.draw(m);
        swapBuffers();
    }

    cleanupRenderer();
    return 0;
}
