#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "checkGLError.hpp"
#include "Shader.hpp"

extern const GLuint WIDTH, HEIGHT;
extern GLFWwindow* window;

void initRenderer();
void clearScreen();
void swapBuffers();
void cleanupRenderer();
void drawCube();
#endif