#ifndef MODEL_HPP
#define MODEL_HPP

#include "bone.hpp"
#include "shader.hpp" 
#include "matrixStack.hpp"
#include "renderer.hpp"
#include <functional>
#include <cmath>

class Model {
    private:
        std::vector<Bone> bones;
        std::function<void()> currentAnimation;
        void drawTorso(MatrixStack &m, Shader &shader);
        void drawHead(MatrixStack &m, Shader &shader);
        void drawArm(MatrixStack &m, Shader &shader ,bool left);
        void drawLeg(MatrixStack &m, Shader &shader ,bool left);
        float elapsedTime;

    public:
        Model();
        void draw(MatrixStack &m, Shader &shader);
        void setAnimation(std::function<void()> animation);
        void update(float deltaTime);
        void animateWalk();
        void updateBoneTransforms();
        void applyBoneTransforms(MatrixStack& m);
};
#endif