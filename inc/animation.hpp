#pragma once

#include "model.hpp"
#include "bone.hpp"
#include <functional>

struct AssimpNodeData
{
    glm::mat4 transformation;
    string name;
    int childrenCount;
    vector<AssimpNodeData> children;
};

class Animation
{
    public:
        Animation() = default;
        Animation(const string& animationPath, Model* model);
        ~Animation();
        Bone* FindBone(const string& name);
        inline float GetTicksPerSecond() const { return mTicksPerSecond; }
        inline float GetDuration() const { return mDuration; }
        inline const AssimpNodeData& GetRootNode() const  { return mRootNode; }
        inline const std::map<string, BoneInfo>& GetBoneIDMap() const { return mBoneInfoMap; }
    private:
        float mTicksPerSecond;
        float mDuration;
        std::vector<Bone> mBones;
        AssimpNodeData mRootNode;
        std::map<string, BoneInfo> mBoneInfoMap;
        void ReadMissingBones(const aiAnimation* animation, Model& model);
        void ReadHeirarchyData(AssimpNodeData& dest, const aiNode* src);
};