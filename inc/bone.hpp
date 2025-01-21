#pragma once

#include <vector>
#include <string>
#include <list>
#include "../libs/include/assimp/scene.h"
#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp"
#include "assimpGLMHelpers.hpp"

struct KeyPosition
{
    glm::vec3 position;
    float timeStamp;
};

struct KeyRotation
{
    glm::quat orientation;
    float timeStamp;
};

struct KeyScale
{
    glm::vec3 scale;
    float timeStamp;
};

class Bone
{
    public:
        Bone(const std::string& name, int ID, const aiNodeAnim* channel);
        void Update(float animationTime);
        glm::mat4 GetLocalTransform();
        std::string GetName();
        int GetBoneID();
        int GetPositionIndex(float animationTime);
        int GetRotationIndex(float animationTime);
        int GetScaleIndex(float animationTime);
    private:
        std::string mName;
        int mBoneID;
        glm::mat4 mLocalTransform;
        int mNumPositionKeys;
        int mNumRotationKeys;
        int mNumScaleKeys;
        std::vector<KeyPosition> mPositionKeys;
        std::vector<KeyRotation> mRotationKeys;
        std::vector<KeyScale> mScaleKeys;

        glm::mat4 InterpolatePosition(float animationTime);
        glm::mat4 InterpolateRotation(float animationTime);
        glm::mat4 InterpolateScale(float animationTime);
        float GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime);
};