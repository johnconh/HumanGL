#include "../inc/animator.hpp"

Animator::Animator(Animation* animation)
{
    mCurrentAnimation = animation;
    mCurrentTime = 0.0f;
    mFinalBoneMatrices.reserve(100);

    for (int i = 0; i < 100; i++)
    {
        mFinalBoneMatrices.push_back(Matrix4());
    }
}

void Animator::UpdateAnimation(float dt)
{
    mDeltaTime = dt;
    if(mCurrentAnimation)
    {
        mCurrentTime += mCurrentAnimation->GetTicksPerSecond() * dt;
        mCurrentTime = fmod(mCurrentTime, mCurrentAnimation->GetDuration());
        CalculateBoneTransform(&mCurrentAnimation->GetRootNode(), Matrix4());
    }
}

void Animator::PlayAnimation(Animation* pAnimation)
{
    mCurrentAnimation = pAnimation;
    mCurrentTime = 0.0f;
}

void Animator::CalculateBoneTransform(const AssimpNodeData* node, const Matrix4& parentTransform)
{
    string nodeName = node->name;
    Matrix4 nodeTransformation = node->transformation;
    Bone* Bone = mCurrentAnimation->FindBone(nodeName);

    if(Bone)
    {
        Bone->Update(mCurrentTime);
        nodeTransformation = Bone->GetLocalTransform();
    }

    Matrix4 globalTransformation = parentTransform * nodeTransformation;

    auto BoneInfoMap = mCurrentAnimation->GetBoneIDMap();
    if(BoneInfoMap.find(nodeName) != BoneInfoMap.end())
    {
        int index = BoneInfoMap[nodeName].id;
        Matrix4 offset = BoneInfoMap[nodeName].BoneOffset;
        mFinalBoneMatrices[index] = globalTransformation * offset;
    }

    for(int i = 0; i < node->childrenCount; i++)
        CalculateBoneTransform(&node->children[i], globalTransformation);

}

