#ifndef BONE_HPP
#define BONE_HPP

#include "matrixStack.hpp"
#include <vector>

class Bone {
    private:
        std::vector<Bone> children;
        Matrix4 localTransform;
        Matrix4 globalTransform;
        Bone* parent;
    public:
        Bone();
        void addChild(Bone& child);
        void setParent(Bone& parent);
        void setLocalTransform(const Matrix4& transform);
        void update();
        void applyTransform(MatrixStack& m);
        Matrix4 getGlobalTransform();
};

#endif