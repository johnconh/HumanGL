#include "../inc/Model.hpp"

Model::Model() {}

void Model::draw(MatrixStack &m, Shader &shader) {
    m.push();
    drawTorso(m, shader);
    drawHead(m, shader);
    drawArm(m, shader, true);
    drawArm(m, shader, false);
    drawLeg(m, shader, true);
    drawLeg(m, shader, false);
    m.pop();
}

void Model::drawTorso(MatrixStack &m, Shader &shader) {
    m.push();
    m.translate(Vector3(0.0f, 0.0f, 0.0f));
    m.scale(Vector3(1.0f, 2.0f, 0.5f));
    shader.setMatrix4("model", m.top());
    drawCube();
    m.pop();
}

void Model::drawHead(MatrixStack &m, Shader &shader) {
    m.push();
    m.translate(Vector3(0.0f, 2.00f, 0.0f));
    m.scale(Vector3(0.75f, 0.75f, 0.75f));
    shader.setMatrix4("model", m.top());
    drawCube();
    m.pop();
}

void Model::drawArm(MatrixStack &m, Shader &shader, bool left) {
    float side = left ? -1.0f : 1.0f;
    // Draw shoulder
    m.push();
    m.translate(Vector3(side * 2.75, 0.50f, 1.0f));
    m.scale(Vector3(0.25f, 1.00f, 0.25f));
    shader.setMatrix4("model", m.top());
    drawCube();
    // Draw hand
    m.push();
    m.translate(Vector3(0.0f, -1.00f, 0.0f));
    m.scale(Vector3(1.0f, 1.0f, 1.0f));
    shader.setMatrix4("model", m.top());
    drawCube();
    m.pop();
    m.pop();
}

void Model::drawLeg(MatrixStack &m, Shader &shader, bool left) {
    float side = left ? -0.5f : 0.5f;
    // Draw hip
    m.push();
    m.translate(Vector3(side, -1.60, 0.0f));
    m.scale(Vector3(0.5f, 1.0f, 0.5f));
    shader.setMatrix4("model", m.top());
    drawCube();
    // Draw foot
    m.push();
    m.translate(Vector3(0.0f, -1.00f, 0.0f));
    m.scale(Vector3(1.0f, 1.0f, 1.0f));
    shader.setMatrix4("model", m.top());
    drawCube();
    m.pop();
    m.pop();
}

