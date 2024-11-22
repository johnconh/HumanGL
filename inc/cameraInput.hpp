#ifndef CAMERA_INPUT_HPP
#define CAMERA_INPUT_HPP

#include <GLFW/glfw3.h>
#include "MatrixStack.hpp"

struct Camera{
    Vector3 position = Vector3(0.0f, 0.0f, 5.0f);
    Vector3 target = Vector3(0.0f, 0.0f, 0.0f);
    Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
    float yaw;
    float pitch;
    float lastX, lastY;
    bool firstMouse = true;
};

void processInput(GLFWwindow* window, Camera& camera, float deltaTime);
void processMouse(GLFWwindow* window, Camera& camera);
Matrix4 updateCamera(Camera& camera);
#endif