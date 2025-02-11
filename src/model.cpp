#include "../inc/model.hpp"


void PrintNodeNames(const aiNode* node) {
    if (node == nullptr) return;

    // Imprimir el nombre del nodo actual
    std::cout << "Node name: " << node->mName.C_Str() << std::endl;

    // Llamar recursivamente para imprimir los nombres de los hijos
    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        PrintNodeNames(node->mChildren[i]);
    }
}

void PrintAllNodeNames(const aiScene* scene) {
    if (scene == nullptr || scene->mRootNode == nullptr) return;

    PrintNodeNames(scene->mRootNode);
}

Model::Model(string const &path)
{
    loadModel(path);
}

void Model::Draw(Shader &shader)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].Draw(shader);
    }
}

void Model::loadModel(string const &path)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
        return;
    }
    //PrintAllNodeNames(scene);
    directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);

}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }

}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        SetVertexBoneDataToDefault(vertex);
        vertex.position = AssimpHelpers::GetVec3(mesh->mVertices[i]);
        vertex.normal = AssimpHelpers::GetVec3(mesh->mNormals[i]);

        if (mesh->mTextureCoords[0])
        {
            Vec2 vec;
            vec.x() = mesh->mTextureCoords[0][i].x;
            vec.y() = mesh->mTextureCoords[0][i].y;
            vertex.texcoord = vec;
        }
        else
            vertex.texcoord = Vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    
    vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    
    ExtractBoneWeightForVertices(vertices, mesh, scene);

    return Mesh(vertices, indices, textures);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{

    vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip)
        {
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }
    return textures;
}

unsigned int TextureFromFile(const char *path, const string &directory)
{
    string filename = string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        CHECK_GL_ERROR(glBindTexture(GL_TEXTURE_2D, textureID));
        CHECK_GL_ERROR(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data));
        CHECK_GL_ERROR (glGenerateMipmap(GL_TEXTURE_2D));

        CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
        CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        stbi_image_free(data);
    }
    else
    {
        cout << "Texture failed to load at path: " << path << endl;
        stbi_image_free(data);
    }

    return textureID;
}

void Model::SetVertexBoneDataToDefault(Vertex& vertex)
{
    for (int i = 0; i < MAX_BONES_INFLUENCE; i++)
    {
        vertex.boneIDs[i] = -1;
        vertex.weights[i] = 0.0f;
    }
}

void Model::SetVertexBoneData(Vertex& vertex, int BoneID, float Weight)
{
    for (int i = 0; i < MAX_BONES_INFLUENCE; ++i)
    {
        if (vertex.weights[i] == 0)
        {
            vertex.weights[i] = Weight;
            vertex.boneIDs[i] = BoneID;
            break;
        }
    }
}

void Model::ExtractBoneWeightForVertices(vector<Vertex>& vertices, aiMesh *mesh, const aiScene *scene)
{ 
    (void)scene;
    auto& boneInfoMap = GetBoneInfoMap();
    auto& boneCounter = GetBoneCounter();

    for (unsigned int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
    {
        int boneID = -1;
        string BoneName = mesh->mBones[boneIndex]->mName.C_Str();
        if (boneInfoMap.find(BoneName) == boneInfoMap.end())
        {
            BoneInfo bi;
            bi.id = boneCounter;
            bi.BoneOffset = AssimpHelpers::ConvertMatrixToMatrix4Format(mesh->mBones[boneIndex]->mOffsetMatrix);;
            boneInfoMap[BoneName] = bi;
            boneID = boneCounter;
            boneCounter++;
        }
        else
        {
            boneID = boneInfoMap[BoneName].id;
        }
        assert (boneID != -1);
        auto weights = mesh->mBones[boneIndex]->mWeights;
        int numWeights = mesh->mBones[boneIndex]->mNumWeights;

        for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
        {
            int VertexID = weights[weightIndex].mVertexId;
            float Weight = weights[weightIndex].mWeight;
            SetVertexBoneData(vertices[VertexID], boneID, Weight);
        }
    }
}