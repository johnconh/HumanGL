#ifndef MODEL_HPP
#define MODEL_HPP

#include "mesh.hpp"
#include "stb_image.h"
#include "../libs/include/assimp/Importer.hpp"
#include "../libs/include/assimp/scene.h"
#include "../libs/include/assimp/postprocess.h"

using namespace std;

unsigned int TextureFromFile(const char *path, const string &directory);

class Model
{
    public:
        vector<Texture> textures_loaded;
        vector<Mesh> meshes;
        string directory;
        bool gammaCorrection;

        Model(string const &path);
        void Draw(Shader &shader);

    private:
        void loadModel(string const &path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};

#endif