#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "shader.hpp"
#include <vector>
#include "checkGLError.hpp"

using namespace std;

#define MAX_BONES_INFLUENCE 4

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord;
    glm::vec3 tangent;
    glm::vec3 bitangent;
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
