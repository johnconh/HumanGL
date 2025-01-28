# pragma once

#include "animation.hpp"
#include "bone.hpp"

class Animator
{
    public:
        Animator(Animation* animation);
        void UpdateAnimation(float dt);
        void PlayAnimation(Animation* pAnimation);
        void CalculateBoneTransform(const AssimpNodeData* node, const glm::mat4& parentTransform);
        inline std::vector<glm::mat4>& GetFinalBoneMatrices() { return mFinalBoneMatrices; }
    private:
        std::vector<glm::mat4> mFinalBoneMatrices;
        Animation* mCurrentAnimation;
        float mCurrentTime;
        float mDeltaTime;
};

