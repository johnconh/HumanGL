#include "../inc/bone.hpp"

Bone::Bone(const std::string& name, int ID, const aiNodeAnim* channel)
    : mName(name), mBoneID(ID), mLocalTransform()
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
    Matrix4 translation = InterpolatePosition(animationTime);
    Matrix4 rotation = InterpolateRotation(animationTime);
    Matrix4 scale = InterpolateScale(animationTime);
    mLocalTransform = translation * rotation * scale;
}

Matrix4 Bone::GetLocalTransform()const {return mLocalTransform;}
std::string Bone::GetName() const {return mName;}
int Bone::GetBoneID() const {return mBoneID;}

int Bone::GetPositionIndex(float animationTime) const
{
    for (int i = 0; i < mNumPositionKeys - 1; i++)
    {
        if (animationTime < mPositionKeys[i + 1].timeStamp)
            return i;
    }
    assert(0);
}

int Bone::GetRotationIndex(float animationTime) const
{
    for (int i = 0; i < mNumRotationKeys - 1; i++)
    {
        if (animationTime < mRotationKeys[i + 1].timeStamp)
            return i;
    }
    assert(0);
}

int Bone::GetScaleIndex(float animationTime) const
{
    for (int i = 0; i < mNumScaleKeys - 1; i++)
    {
        if (animationTime < mScaleKeys[i + 1].timeStamp)
            return i;
    }
    assert(0);
}

Matrix4 Bone::InterpolatePosition(float animationTime)
{
    if (1 == mNumPositionKeys)
        return  Matrix4::translate(mPositionKeys[0].position.x(), mPositionKeys[0].position.y(), mPositionKeys[0].position.z());

    int PositionIndex = GetPositionIndex(animationTime);
    int NextPositionIndex = (PositionIndex + 1);
    assert(NextPositionIndex < mNumPositionKeys);
    float scaleFactor = GetScaleFactor(mPositionKeys[PositionIndex].timeStamp, mPositionKeys[NextPositionIndex].timeStamp, animationTime);
    Vec3 finalPosition = Vec3::mix(mPositionKeys[PositionIndex].position, mPositionKeys[NextPositionIndex].position, scaleFactor);
    return Matrix4::translate(finalPosition.x(), finalPosition.y(), finalPosition.z());
}

Matrix4 Bone::InterpolateRotation(float animationTime)
{
    if (1 == mNumRotationKeys)
    {
        auto rotation = mRotationKeys[0].orientation.normalize();
        return rotation.toMatrix();
    }

    int RotationIndex = GetRotationIndex(animationTime);
    int NextRotationIndex = (RotationIndex + 1);
    assert(NextRotationIndex < mNumRotationKeys);
    float scaleFactor = GetScaleFactor(mRotationKeys[RotationIndex].timeStamp, mRotationKeys[NextRotationIndex].timeStamp, animationTime);
    Quaternion finalRotation = Quaternion::slerp(mRotationKeys[RotationIndex].orientation, mRotationKeys[NextRotationIndex].orientation, scaleFactor).normalize();
    return finalRotation.toMatrix();
}

Matrix4 Bone::InterpolateScale(float animationTime)
{
    if (1 == mNumScaleKeys)
        return Matrix4::scale(mScaleKeys[0].scale.x(), mScaleKeys[0].scale.y(), mScaleKeys[0].scale.z());

    int ScaleIndex = GetScaleIndex(animationTime);
    int NextScaleIndex = (ScaleIndex + 1);
    assert(NextScaleIndex < mNumScaleKeys);
    float scaleFactor = GetScaleFactor(mScaleKeys[ScaleIndex].timeStamp, mScaleKeys[NextScaleIndex].timeStamp, animationTime);
    Vec3 finalScale = Vec3::mix(mScaleKeys[ScaleIndex].scale, mScaleKeys[NextScaleIndex].scale, scaleFactor);
    return Matrix4::scale(finalScale.x(), finalScale.y(), finalScale.z());
}

float Bone::GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime) const
{
    float scaleFactor = 0.0f;
    float midWayLength = animationTime - lastTimeStamp;
    float framesDiff = nextTimeStamp - lastTimeStamp;
    scaleFactor = midWayLength / framesDiff;
    return scaleFactor;
}


