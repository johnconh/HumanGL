#ifndef MATRIXSTACK_HPP
#define MATRIXSTACK_HPP

#include <stack>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class MatrixStack {
    private:
        std::stack<glm::mat4> stack;
    public:
        MatrixStack();
        void push();
        void pop();
        void loadIdentity();
        void multiply(glm::mat4 matrix);
        void translate(glm::vec3 translation);
        void scale(glm::vec3 scale);
        glm::mat4 top() const;
};

#endif