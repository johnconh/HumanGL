#include "../inc/animation.hpp"

Animation::Animation(const string& animationPath, Model* model)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(animationPath, aiProcess_Triangulate);
    assert(scene && scene->mRootNode);
    auto animation = scene->mAnimations[0];
    mDuration = animation->mDuration;
    mTicksPerSecond = animation->mTicksPerSecond;
    aiMatrix4x4 globalTransformation = scene->mRootNode->mTransformation;
    globalTransformation = globalTransformation.Inverse();
    ReadHeirarchyData(mRootNode, scene->mRootNode);
    ReadMissingBones(animation, *model);
}

Animation::~Animation(){}

Bone* Animation::FindBone(const string& name)
{
    auto iter = std::find_if(mBones.begin(), mBones.end(), [&](const Bone& Bone)
    {
        return Bone.GetName() == name;
    });
    if (iter == mBones.end()) return nullptr;
    else return &(*iter);
}

void Animation::ReadMissingBones(const aiAnimation* animation, Model& model)
{
    int size = animation->mNumChannels;
    auto& boneInfoMap = model.GetBoneInfoMap();
    int& boneCounter = model.GetBoneCounter();

    for (int i = 0; i < size; i++)
    {
        auto channel = animation->mChannels[i];
        string boneName = channel->mNodeName.data;
        if (boneInfoMap.find(boneName) == boneInfoMap.end())
        {
            boneInfoMap[boneName].id = boneCounter;
            boneCounter++;
        }
        mBones.push_back(Bone(boneName, boneInfoMap[boneName].id, channel));
    }
    mBoneInfoMap = boneInfoMap;
}

void Animation::ReadHeirarchyData(AssimpNodeData& dest, const aiNode* src)
{
    assert(src);
    dest.name = src->mName.data;
    dest.transformation = AssimpHelpers::ConvertMatrixToMatrix4Format(src->mTransformation);
    dest.childrenCount = src->mNumChildren;

    for (unsigned int i = 0; i < src->mNumChildren; i++)
    {
        AssimpNodeData newData;
        ReadHeirarchyData(newData, src->mChildren[i]);
        dest.children.push_back(newData);
    }
}