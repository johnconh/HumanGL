#include "../inc/cameraInput.hpp"

void processInput(GLFWwindow* window, Camera& camera, float deltaTime) {
    float cameraSpeed = 2.5f * deltaTime;
    
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.position = camera.position + normalize(sub(camera.target, camera.position)) * cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.position = camera.position - normalize(sub(camera.target, camera.position)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.position = camera.position - normalize(cross(camera.up, sub(camera.target, camera.position))) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.position = camera.position + normalize(cross(camera.up, sub(camera.target, camera.position))) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.position.y += cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.position.y -= cameraSpeed;
}

void processMouse(GLFWwindow* window, Camera& camera) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    if(camera.firstMouse) {
        camera.lastX = xpos;
        camera.lastY = ypos;
        camera.firstMouse = false;
    }

    float xoffset = xpos - camera.lastX;
    float yoffset = camera.lastY - ypos;
    camera.lastX = xpos;
    camera.lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera.yaw += xoffset;
    camera.pitch += yoffset;

    if(camera.pitch > 89.0f)
        camera.pitch = 89.0f;
    if(camera.pitch < -89.0f)
        camera.pitch = -89.0f;

    Vector3 front;
    front.x = cos(radians(camera.yaw)) * cos(radians(camera.pitch));
    front.y = sin(radians(camera.pitch));
    front.z = sin(radians(camera.yaw)) * cos(radians(camera.pitch));
    camera.target = camera.position + normalize(front);
}

Matrix4 updateCamera(Camera& camera) {
    return lookAt(camera.position, camera.target, camera.up);
}