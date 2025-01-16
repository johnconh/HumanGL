#include "../inc/renderer.hpp"


int main() {
    initRenderer();

    while(!glfwWindowShouldClose(window)) {

        clearScreen();
        swapBuffers();
    }

    cleanupRenderer();
    return 0;
}
