#ifndef MESH_HPP
#define MESH_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "shader.hpp"
#include <vector>

using namespace std;

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord;
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
        void draw(Shader &shader);

    private:
        // render data
        unsigned int VAO, VBO, EBO;
        void setupMesh();
};

#endif