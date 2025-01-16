#ifndef MESH_HPP
#define MESH_HPP

#include "glm/glm.hpp"
#include <vector>


struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord;
};

struct Texture
{
    unsigned int id;
    std::string type;
}

class Mesh
{
    public:

}

#endif