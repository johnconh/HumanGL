#pragma once

#include "shader.hpp"
#include <vector>
#include "checkGLError.hpp"

using namespace std;

#define MAX_BONES_INFLUENCE 4

struct Vertex
{
    Vec3 position;
    Vec3 normal;
    Vec2 texcoord;
    Vec3 tangent;
    Vec3 bitangent;
    int boneIDs[MAX_BONES_INFLUENCE];
    float weights[MAX_BONES_INFLUENCE];
};

struct Texture
{
    unsigned int id;
    string type;
    string path;
};

class Mesh
{
    public:
        // mesh data
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;

        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
        void Draw(Shader &shader);

    private:
        // render data
        unsigned int VAO, VBO, EBO;
        void setupMesh();
};
