# pragma once

#include "animation.hpp"
#include "bone.hpp"

class Animator
{
    public:
        Animator(Animation* animation);
        void UpdateAnimation(float dt);
        void PlayAnimation(Animation* pAnimation);
        void CalculateBoneTransform(const AssimpNodeData* node, const Matrix4& parentTransform);
        inline std::vector<Matrix4>& GetFinalBoneMatrices() { return mFinalBoneMatrices; };
    private:
        std::vector<Matrix4> mFinalBoneMatrices;
        Animation* mCurrentAnimation;
        float mCurrentTime;
        float mDeltaTime;
};

