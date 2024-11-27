#include "../inc/bone.hpp"

Bone::Bone() {
    localTransform = Matrix4();
    globalTransform = Matrix4();
    parent = nullptr;
}

void Bone::addChild(Bone& child) {
    children.push_back(child);
}

void Bone::setParent(Bone& parent) {
    this->parent = &parent;
}

void Bone::setLocalTransform(const Matrix4& transform) {
    localTransform = transform;
}

void Bone::update() {
    if(parent) {
        globalTransform = parent->getGlobalTransform() * localTransform;
    } else {
        globalTransform = localTransform;
    }

    for(Bone& child : children) {
        child.update();
    }
}

Matrix4 Bone::getGlobalTransform() {
    return globalTransform;
}

void Bone::applyTransform(MatrixStack& m) {
    m.push();
    m.applyMatrix(globalTransform);
}
