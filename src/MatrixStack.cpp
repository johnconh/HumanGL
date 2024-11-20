#include "../inc/MatrixStack.hpp"

MatrixStack::MatrixStack() {
    stack.push(glm::mat4(1.0f));
}

void MatrixStack::push() {
    stack.push(stack.top());
}

void MatrixStack::pop() {
    stack.pop();
}

void MatrixStack::loadIdentity() {
    stack.top() = glm::mat4(1.0f);
}

void MatrixStack::multiply(glm::mat4 matrix) {
    stack.top() *=  matrix;
}

void MatrixStack::translate(glm::vec3 translation) {
    stack.top() = glm::translate(stack.top(), translation);
}

void MatrixStack::scale(glm::vec3 scale) {
    stack.top() = glm::scale(stack.top(), scale);
}

glm::mat4 MatrixStack::top() const {
    return stack.top();
}