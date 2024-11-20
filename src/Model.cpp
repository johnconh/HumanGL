#include "../inc/Model.hpp"
#include "../inc/checkGLError.hpp"
#include "../inc/Renderer.hpp"

Model::Model() {

}

void Model::draw(MatrixStack &m) {
    m.push();
    drawHead(m);

}

void Model::drawTorso(MatrixStack &m) {
    m.push();
    m.multiply(glm::translate(glm::mat4(1.0f), glm::vec3(0.75f, 2.0f, 0.5f)));
    CHECK_GL_ERROR(glLoadMatrixf(&m.top()[0][0]));
    m.pop();
}

void Model::drawHead(MatrixStack &m) {
    m.push();
    m.multiply(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.5f, 0.0f)));
    m.multiply(glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f)));
    CHECK_GL_ERROR(glLoadMatrixf(&m.top()[0][0]));
    drawCube();
    m.pop();
}

void Model::drawArm(MatrixStack &m, bool left) {
    float side = left ? -1.0f : 1.0f;

    // Draw shoulder
    m.push();
    m.multiply(glm::translate(glm::mat4(1.0f), glm::vec3(side * 0.60f, 1.5f, 0.0f)));
    m.multiply(glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 1.00f, 0.35f)));
    CHECK_GL_ERROR(glLoadMatrixf(&m.top()[0][0]));
    drawCube();

    // Draw hand
    m.push();
    m.multiply(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.00f, 0.0f)));
    m.multiply(glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 1.00f, 0.35f)));
    CHECK_GL_ERROR(glLoadMatrixf(&m.top()[0][0]));
    drawCube();
    m.pop();

    m.pop();
}

void Model::drawLeg(MatrixStack &m, bool left) {
    float side = left ? -0.5f : 0.5f;

    // Draw hip
    m.push();
    m.multiply(glm::translate(glm::mat4(1.0f), glm::vec3(side, -1.5f, 0.0f)));
    m.multiply(glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 1.5f, 0.35f)));
    CHECK_GL_ERROR(glLoadMatrixf(&m.top()[0][0]));
    drawCube();

    // Draw foot
    m.multiply(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.5f, 0.0f)));
    m.multiply(glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 1.00f, 0.35f)));
    CHECK_GL_ERROR(glLoadMatrixf(&m.top()[0][0]));
    drawCube();
    m.pop();
}

