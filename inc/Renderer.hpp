#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GLFW/glfw3.h>
#include "Shader.hpp"

extern GLFWwindow* window;

void initRenderer();
void clearScreen();
void swapBuffers();
void cleanupRenderer();
void drawCube();
void setupCamera(Shader &shader); 

#endif