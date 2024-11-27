#include "../inc/model.hpp"

Model::Model(){

    Bone torso;
    bones.push_back(torso);

    Bone head;
    head.setParent(torso);
    bones.push_back(head);

    Bone leftUpperArm;
    leftUpperArm.setParent(torso);
    bones.push_back(leftUpperArm);

    Bone leftLowerArm;
    leftLowerArm.setParent(leftUpperArm);
    bones.push_back(leftLowerArm);

    Bone rightUpperArm;
    rightUpperArm.setParent(torso);
    bones.push_back(rightUpperArm);

    Bone rightLowerArm;
    rightLowerArm.setParent(rightUpperArm);
    bones.push_back(rightLowerArm);

    Bone leftUpperLeg;
    leftUpperLeg.setParent(torso);
    bones.push_back(leftUpperLeg);

    Bone leftLowerLeg;
    leftLowerLeg.setParent(leftUpperLeg);
    bones.push_back(leftLowerLeg);

    Bone rightUpperLeg;
    rightUpperLeg.setParent(torso);
    bones.push_back(rightUpperLeg);

    Bone rightLowerLeg;
    rightLowerLeg.setParent(rightUpperLeg);
    bones.push_back(rightLowerLeg);

    torso.addChild(head);
    torso.addChild(leftUpperArm);
    torso.addChild(rightUpperArm);
    torso.addChild(leftUpperLeg);
    torso.addChild(rightUpperLeg);

    leftUpperArm.addChild(leftLowerArm);
    rightUpperArm.addChild(rightLowerArm);
    leftUpperLeg.addChild(leftLowerLeg);
    rightUpperLeg.addChild(rightLowerLeg);
    //setAnimation([this]() { animateWalk(); });
}

void Model::updateBoneTransforms() {
    for(Bone& bone : bones) {
        bone.update();
    }
}

void Model::applyBoneTransforms(MatrixStack& m) {
    for(Bone& bone : bones) {
        bone.applyTransform(m);
    }
}

void Model::draw(MatrixStack &m, Shader &shader) {
    m.push();
    Vector3 translation (bones[0].getGlobalTransform().m[3][0], bones[0].getGlobalTransform().m[3][1], bones[0].getGlobalTransform().m[3][2]);
    m.translate(translation);
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
    m.push();
    m.translate(Vector3(side * 2.50, 0.5f, 0.0f));
    m.scale(Vector3(0.25f, 1.00f, 0.25f));
    shader.setVector3("objectColor", Vector3(255.0f / 255.0f, 224.0f / 255.0f, 185.0f / 255.0f));
    shader.setMatrix4("model", m.top());
    drawCube();
    m.push();
    m.translate(Vector3(0.0f, -1.00f, 0.0f));
    m.scale(Vector3(1.00f, 1.25f, 1.00f));
    shader.setMatrix4("model", m.top());
    drawCube();
    m.pop();
    m.pop();
}

void Model::drawLeg(MatrixStack &m, Shader &shader, bool left) {
    float side = left ? -0.5f : 0.5f;
    m.push();
    m.translate(Vector3(side, -1.50, 0.0f));
    m.scale(Vector3(0.5f, 1.0f, 0.5f));
    shader.setVector3("objectColor", Vector3(38.0f / 255.0f, 57.0f / 255.0f, 75.0f / 255.0f));
    shader.setMatrix4("model", m.top());
    drawCube();
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
}