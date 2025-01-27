#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include "mesh.hpp"
#include "stb_image.h"
#include "../libs/include/assimp/Importer.hpp"
#include "../libs/include/assimp/scene.h"
#include "../libs/include/assimp/postprocess.h"
#include "assimpGLMHelpers.hpp"

using namespace std;

unsigned int TextureFromFile(const char *path, const string &directory);

struct BoneInfo
{
    int id;
    glm::mat4 BoneOffset;
};

class Model
{
    public:
        vector<Texture> textures_loaded;
        vector<Mesh> meshes;
        string directory;
        bool gammaCorrection;

        Model(string const &path);
        void Draw(Shader &shader);
        inline auto& GetBoneInfoMap() { return m_BoneInfoMap; }
        inline int& GetBoneCounter() { return m_BoneCounter; }

    private:
        std::map <string, BoneInfo> m_BoneInfoMap;
        int m_BoneCounter = 0;
        void SetVertexBoneDataToDefault(Vertex& vertex);
        void SetVertexBoneData(Vertex& vertex, int BoneID, float Weight);
        void ExtractBoneWeightForVertices(vector<Vertex>& vertices, aiMesh *mesh, const aiScene *scene);
        void loadModel(string const &path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};

