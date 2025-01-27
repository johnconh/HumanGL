#include "../inc/bone.hpp"

Bone::Bone(const std::string& name, int ID, const aiNodeAnim* channel)
    : mName(name), mBoneID(ID), mLocalTransform(1.0f)
{
    mNumPositionKeys = channel->mNumPositionKeys;
    mNumRotationKeys = channel->mNumRotationKeys;
    mNumScaleKeys = channel->mNumScalingKeys;

    for (int i = 0; i < mNumPositionKeys; i++)
    {
        aiVector3D aiPos = channel->mPositionKeys[i].mValue;
        float timeStamp = channel->mPositionKeys[i].mTime;
        KeyPosition key;
        key.position = AssimpGLMHelpers::GetGLMVec(aiPos);
        key.timeStamp = timeStamp;
        mPositionKeys.push_back(key);
    }

    for (int i = 0; i < mNumRotationKeys; i++)
    {
        aiQuaternion aiRot = channel->mRotationKeys[i].mValue;
        float timeStamp = channel->mRotationKeys[i].mTime;
        KeyRotation key;
        key.orientation = AssimpGLMHelpers::GetGLMQuat(aiRot);
        key.timeStamp = timeStamp;
        mRotationKeys.push_back(key);
    }

    for (int i = 0; i < mNumScaleKeys; i++)
    {
        aiVector3D aiScale = channel->mScalingKeys[i].mValue;
        float timeStamp = channel->mScalingKeys[i].mTime;
        KeyScale key;
        key.scale = AssimpGLMHelpers::GetGLMVec(aiScale);
        key.timeStamp = timeStamp;
        mScaleKeys.push_back(key);
    }
}

void Bone::Update(float animationTime)
{
    glm::mat4 translation = InterpolatePosition(animationTime);
    glm::mat4 rotation = InterpolateRotation(animationTime);
    glm::mat4 scale = InterpolateScale(animationTime);
    mLocalTransform = translation * rotation * scale;
}

glm::mat4 Bone::GetLocalTransform(){return mLocalTransform;}
std::string Bone::GetName() const {return mName;}
int Bone::GetBoneID(){return mBoneID;}

int Bone::GetPositionIndex(float animationTime)
{
    for (int i = 0; i < mNumPositionKeys - 1; i++)
    {
        if (animationTime < mPositionKeys[i + 1].timeStamp)
            return i;
    }
    assert(0);
}

int Bone::GetRotationIndex(float animationTime)
{
    for (int i = 0; i < mNumRotationKeys - 1; i++)
    {
        if (animationTime < mRotationKeys[i + 1].timeStamp)
            return i;
    }
    assert(0);
}

int Bone::GetScaleIndex(float animationTime)
{
    for (int i = 0; i < mNumScaleKeys - 1; i++)
    {
        if (animationTime < mScaleKeys[i + 1].timeStamp)
            return i;
    }
    assert(0);
}

glm::mat4 Bone::InterpolatePosition(float animationTime)
{
    if (1 == mNumPositionKeys)
        return  glm::translate(glm::mat4(1.0f), mPositionKeys[0].position);

    int PositionIndex = GetPositionIndex(animationTime);
    int NextPositionIndex = (PositionIndex + 1);
    assert(NextPositionIndex < mNumPositionKeys);
    float scaleFactor = GetScaleFactor(mPositionKeys[PositionIndex].timeStamp, mPositionKeys[NextPositionIndex].timeStamp, animationTime);
    glm::vec3 finalPosition = glm::mix(mPositionKeys[PositionIndex].position, mPositionKeys[NextPositionIndex].position, scaleFactor);
    return glm::translate(glm::mat4(1.0f), finalPosition);
}

glm::mat4 Bone::InterpolateRotation(float animationTime)
{
    if (1 == mNumRotationKeys)
    {
        auto rotation = glm::normalize(mRotationKeys[0].orientation);
        return glm::toMat4(rotation);
    }

    int RotationIndex = GetRotationIndex(animationTime);
    int NextRotationIndex = (RotationIndex + 1);
    assert(NextRotationIndex < mNumRotationKeys);
    float scaleFactor = GetScaleFactor(mRotationKeys[RotationIndex].timeStamp, mRotationKeys[NextRotationIndex].timeStamp, animationTime);
    glm::quat finalRotation = glm::slerp(mRotationKeys[RotationIndex].orientation, mRotationKeys[NextRotationIndex].orientation, scaleFactor);
    finalRotation = glm::normalize(finalRotation);
    return glm::toMat4(finalRotation);
}

glm::mat4 Bone::InterpolateScale(float animationTime)
{
    if (1 == mNumScaleKeys)
        return glm::scale(glm::mat4(1.0f), mScaleKeys[0].scale);

    int ScaleIndex = GetScaleIndex(animationTime);
    int NextScaleIndex = (ScaleIndex + 1);
    assert(NextScaleIndex < mNumScaleKeys);
    float scaleFactor = GetScaleFactor(mScaleKeys[ScaleIndex].timeStamp, mScaleKeys[NextScaleIndex].timeStamp, animationTime);
    glm::vec3 finalScale = glm::mix(mScaleKeys[ScaleIndex].scale, mScaleKeys[NextScaleIndex].scale, scaleFactor);
    return glm::scale(glm::mat4(1.0f), finalScale);
}

float Bone::GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime)
{
    float scaleFactor = 0.0f;
    float midWayLength = animationTime - lastTimeStamp;
    float framesDiff = nextTimeStamp - lastTimeStamp;
    scaleFactor = midWayLength / framesDiff;
    return scaleFactor;
}


