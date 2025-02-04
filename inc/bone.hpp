#pragma once

#include <vector>
#include <string>
#include <list>
#include "../libs/include/assimp/scene.h"
#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp"
#include "assimpGLMHelpers.hpp"
#include "vector.hpp"
#include "quaternion.hpp"

struct KeyPosition
{
    Vec3 position;
    float timeStamp;
};

struct KeyRotation
{
    Quaternion orientation;
    float timeStamp;
};

struct KeyScale
{
    Vec3 scale;
    float timeStamp;
};

class Bone
{
    public:
        Bone(const std::string& name, int ID, const aiNodeAnim* channel);
        void Update(float animationTime);
        Matrix4 GetLocalTransform() const;
        std::string GetName() const;
        int GetBoneID() const;
        int GetPositionIndex(float animationTime) const;
        int GetRotationIndex(float animationTime) const;
        int GetScaleIndex(float animationTime) const;
    private:
        std::string mName;
        int mBoneID;
        Matrix4 mLocalTransform;
        int mNumPositionKeys;
        int mNumRotationKeys;
        int mNumScaleKeys;
        std::vector<KeyPosition> mPositionKeys;
        std::vector<KeyRotation> mRotationKeys;
        std::vector<KeyScale> mScaleKeys;

        Matrix4 InterpolatePosition(float animationTime);
        Matrix4 InterpolateRotation(float animationTime);
        Matrix4 InterpolateScale(float animationTime);
        float GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime) const;
};