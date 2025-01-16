#ifndef MESH_HPP
#define MESH_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "shader.hpp"
#include <vector>

using namespace std;

#define MAX_BONES 4

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    int boneIDs[MAX_BONES];
    float weights[MAX_BONES];
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

#endif