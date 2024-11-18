#ifndef MATRIXSTACK_HPP
#define MATRIXSTACK_HPP

#include <stack>
#include <glm/glm.hpp>

class MatrixStack {
    private:
        std::stack<glm::mat4> stack;
    public:
        MatrixStack();
        void push();
        void pop();
        void loadIdentity();
        void multiply(glm::mat4 matrix);
        glm::mat4 top() const;
};

#endif