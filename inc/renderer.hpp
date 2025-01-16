#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "checkGLError.hpp"


extern const GLuint WIDTH, HEIGHT;
extern GLFWwindow* window;
using namespace std;

void initRenderer();
void clearScreen();
void swapBuffers();
void cleanupRenderer();

#endif