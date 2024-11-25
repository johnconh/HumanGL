#ifndef MODEL_HPP
#define MODEL_HPP

#include "Shader.hpp" 
#include "MatrixStack.hpp"
#include "Renderer.hpp"
#include <functional>
#include <cmath>

class Model {
    private:
        Matrix4 torsoMatrix;
        Matrix4 headMatrix;
        Matrix4 leftUpperArmMatrix;
        Matrix4 leftLowerArmMatrix;
        Matrix4 rightUpperArmMatrix;
        Matrix4 rightLowerArmMatrix;
        Matrix4 leftUpperLegMatrix;
        Matrix4 leftLowerLegMatrix;
        Matrix4 rightUpperLegMatrix;
        Matrix4 rightLowerLegMatrix;
        void drawTorso(MatrixStack &m, Shader &shader);
        void drawHead(MatrixStack &m, Shader &shader);
        void drawArm(MatrixStack &m, Shader &shader ,bool left);
        void drawLeg(MatrixStack &m, Shader &shader ,bool left);
        float elapsedTime;
        std::function<void()> currentAnimation;

    public:
        Model();
        void draw(MatrixStack &m, Shader &shader);
        void setAnimation(std::function<void()> animation);
        void update(float deltaTime);
        void animateWalk();
};
#endif