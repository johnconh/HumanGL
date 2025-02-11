#include "../inc/animator.hpp"

Animator::Animator(Animation* animation)
{
    mCurrentAnimation = animation;
    mCurrentTime = 0.0f;
    mFinalBoneMatrices.reserve(100);

    for (int i = 0; i < 100; i++)
    {
        mFinalBoneMatrices.push_back(Matrix4::identity());
    }
}

void Animator::UpdateAnimation(float dt)
{
    mDeltaTime = dt;
    if(mCurrentAnimation && !isPause)
    {
        mCurrentTime += mCurrentAnimation->GetTicksPerSecond() * dt;
        mCurrentTime = fmod(mCurrentTime, mCurrentAnimation->GetDuration());
        CalculateBoneTransform(&mCurrentAnimation->GetRootNode(), Matrix4::identity());
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
        // if(nodeName == "mixamorig_Head")
        // {
        //     Matrix4 scaleMatrix = Matrix4::scale(2.0f, 2.0f, 2.0f);
        //     nodeTransformation = nodeTransformation * scaleMatrix;
        // }
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

void Animator::setCurrentTime(float time)
{
   mCurrentTime = fmod(time, mCurrentAnimation->GetDuration());
   CalculateBoneTransform(&mCurrentAnimation->GetRootNode(), Matrix4::identity());
}

float Animator::getDuration() const
{
    return mCurrentAnimation ? mCurrentAnimation->GetDuration() : 0.0f;
}

float Animator::getTicksPerSecond() const
{
    return mCurrentAnimation ? mCurrentAnimation->GetTicksPerSecond() : 0.0f;
}

void Animator::setPause(bool pause)
{
    isPause = pause;
}
