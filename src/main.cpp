#include "../inc/shader.hpp"
#include "../inc/renderer.hpp"
#include "../inc/model.hpp"
#include "../inc/matrixStack.hpp"
#include "../inc/cameraInput.hpp"

int main() {
    initRenderer();

    Camera camera;
    Model humanModel;
    MatrixStack m;
    Shader shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    Matrix4 projection = perspective(45.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    Matrix4 view = lookAt(camera.position, camera.target, camera.up);

    float lastframe = 0.0f;
    while(!glfwWindowShouldClose(window)) {
        float currentframe = glfwGetTime();
        float deltaTime = currentframe - lastframe;
        lastframe = currentframe;
        
        humanModel.update(deltaTime);
        humanModel.updateBoneTransforms();
        //humanModel.applyBoneTransforms(m);
        processInput(window, camera, deltaTime);
        //processMouse(window, camera);

        clearScreen();
        view = updateCamera(camera);
        shader.use();
        shader.setMatrix4("projection", projection);
        shader.setMatrix4("view", view);
        humanModel.draw(m, shader);
        swapBuffers();
    }

    cleanupRenderer();
    return 0;
}
