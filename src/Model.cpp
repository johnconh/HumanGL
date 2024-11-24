#include "../inc/Model.hpp"

Model::Model(): elapsedTime(0.0f), currentAnimation(nullptr){
    torsoMatrix = Matrix4();
    headMatrix = Matrix4();
    leftUpperArmMatrix = Matrix4();
    leftLowerArmMatrix = Matrix4();
    rightUpperArmMatrix = Matrix4();
    rightLowerArmMatrix = Matrix4();
    leftUpperLegMatrix = Matrix4();
    leftLowerLegMatrix = Matrix4();
    rightUpperLegMatrix = Matrix4();
    rightLowerLegMatrix = Matrix4();
    setAnimation([this]() { animateWalk(); });
}

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
    shader.setVector3("objectColor", Vector3(1.0f, 0.0f, 0.0f));
    shader.setMatrix4("model", m.top());
    drawCube();
    m.pop();
}

void Model::drawHead(MatrixStack &m, Shader &shader) {
    m.push();
    m.translate(Vector3(0.0f, 1.85f, 0.0f));
    m.scale(Vector3(0.75f, 0.75f, 0.75f));
    shader.setVector3("objectColor", Vector3(255.0f / 255.0f, 224.0f / 255.0f, 185.0f / 255.0f));
    shader.setMatrix4("model", m.top());
    drawCube();
    m.pop();
}

void Model::drawArm(MatrixStack &m, Shader &shader, bool left) {
    float side = left ? -1.0f : 1.0f;
    // Draw shoulder
    m.push();
    m.translate(Vector3(side * 2.50, 0.5f, 0.0f));
    m.scale(Vector3(0.25f, 1.00f, 0.25f));
    shader.setVector3("objectColor", Vector3(255.0f / 255.0f, 224.0f / 255.0f, 185.0f / 255.0f));
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
    m.translate(Vector3(side, -1.50, 0.0f));
    m.scale(Vector3(0.5f, 1.0f, 0.5f));
    shader.setVector3("objectColor", Vector3(38.0f / 255.0f, 57.0f / 255.0f, 75.0f / 255.0f));
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

void Model::setAnimation(std::function<void()> animation) {
    currentAnimation = animation;
    elapsedTime = 0.0f;
}

void Model::update(float deltaTime) {
    elapsedTime += deltaTime;
    if (currentAnimation != nullptr) {
        currentAnimation();
    }
}

void Model::animateWalk() {
    float walkCycle = std::sin(elapsedTime * 3.14159f * 2.0f);

    float upperLegAngle = walkCycle * 30.0f;
    leftUpperLegMatrix.rotateX(radians(upperLegAngle));
    rightUpperLegMatrix.rotateX(radians(-upperLegAngle));

    float lowerLegAngle = walkCycle * 50.0f;
    leftLowerLegMatrix.rotateX(radians(lowerLegAngle));
    rightLowerLegMatrix.rotateX(radians(-lowerLegAngle));

    float upperArmAngle = -walkCycle * 20.0f;
    leftUpperArmMatrix.rotateX(radians(upperArmAngle));
    rightUpperArmMatrix.rotateX(radians(-upperArmAngle));

    float lowerArmAngle = walkCycle * 25.0f;
    leftLowerArmMatrix.rotateX(radians(lowerArmAngle));
    rightLowerArmMatrix.rotateX(radians(-lowerArmAngle));

    float fowardSpeed = 0.5f;
    float fowardTranslation = elapsedTime * fowardSpeed;
    torsoMatrix.translate(Vector3(0.0f, 0.0f, fowardTranslation));
}