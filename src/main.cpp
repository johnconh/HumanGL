#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../inc/shader.hpp"
#include "../inc/camera.hpp"
#include "../inc/imguiManager.hpp"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

const unsigned int WIDTH = 800, HEIGHT = 600;
Camera camera(Vec3(0.0f, 0.0f, 3.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;
bool isMouseButtonPressed = false;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "HumanGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
 

    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLEW" << endl;
        exit(1);
    }

    ImGuiManager::init(window);

    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);


    Shader ourShader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    Model ourModel("resources/model/akai/akai.dae");
    Animation ourAnimation("resources/animation/Idle.dae", &ourModel);
    Animator ourAnimator(&ourAnimation);

    //draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        ourAnimator.UpdateAnimation(deltaTime); 
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGuiManager::render(ourAnimator, ourModel, deltaTime);

        ourShader.use();

        Matrix4 projection = Matrix4::perspective(camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
        Matrix4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        auto finalBoneMatrices = ourAnimator.GetFinalBoneMatrices();
        for (unsigned int i = 0; i < finalBoneMatrices.size(); i++)
            ourShader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", finalBoneMatrices[i]);
        
        Matrix4 model = Matrix4::identity();
        model = model * Matrix4::translate(0.0f, -0.9f, 0.0f);
        //model = model * Matrix4::scale(0.5f, 0.5f, 0.5f);
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGuiManager::shutdown();
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        isMouseButtonPressed = true;
    } else {
        isMouseButtonPressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    (void)window;
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    (void)window;

    if (!isMouseButtonPressed) {
        return;
    }

    if (firstMouse) {
        lastX = static_cast<float>(xpos);
        lastY = static_cast<float>(ypos);
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    (void)window;
    (void)xoffset;
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}