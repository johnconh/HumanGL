#include "../inc/Shader.hpp"
#include "../inc/Renderer.hpp"
#include "../inc/Model.hpp"
#include "../inc/MatrixStack.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


int main() {

    initRenderer();

    Model humanModel;
    MatrixStack m;
    Shader shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    Matrix4 projection = perspective(45.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    Matrix4 view = lookAt(Vector3(0.0f, 0.0f, 10.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

    while(!glfwWindowShouldClose(window)) {
        clearScreen();
        shader.use();
        shader.setMatrix4("projection", projection);
        shader.setMatrix4("view", view);
        humanModel.draw(m, shader);
        swapBuffers();
    }

    cleanupRenderer();
    return 0;
}
