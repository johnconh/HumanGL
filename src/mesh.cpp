#include "../inc/mesh.hpp"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
}

void Mesh::Draw(Shader &shader) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        string number;
        string name = textures[i].type;
        if (name == "texture_diffuse") {
            number = to_string(diffuseNr++);
        } else if (name == "texture_specular") {
            number = to_string(specularNr++);
        } else if (name == "texture_normal") {
            number = to_string(normalNr++);
        } else if (name == "texture_height") {
            number = to_string(heightNr++);
        }
        glUniform1i(glGetUniformLocation(shader.id, (name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    // draw mesh
    CHECK_GL_ERROR(glBindVertexArray(VAO));
    CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0));
    CHECK_GL_ERROR(glBindVertexArray(0));

    CHECK_GL_ERROR(glActiveTexture(GL_TEXTURE0));

}

void Mesh::setupMesh() {
    CHECK_GL_ERROR(glGenVertexArrays(1, &VAO));
    CHECK_GL_ERROR(glGenBuffers(1, &VBO));
    CHECK_GL_ERROR(glGenBuffers(1, &EBO));

    CHECK_GL_ERROR(glBindVertexArray(VAO));
    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, VBO));

    CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW));

    CHECK_GL_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
    CHECK_GL_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW));
    // vertex positions
    CHECK_GL_ERROR(glEnableVertexAttribArray(0));
    CHECK_GL_ERROR(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0));
    // vertex normals
    CHECK_GL_ERROR(glEnableVertexAttribArray(1));
    CHECK_GL_ERROR(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal)));
    // vertex texture coords
    CHECK_GL_ERROR(glEnableVertexAttribArray(2));
    CHECK_GL_ERROR(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord)));
    // vertex tangent
    CHECK_GL_ERROR(glEnableVertexAttribArray(3));
    CHECK_GL_ERROR(glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent)));
    // vertex bitangent
    CHECK_GL_ERROR(glEnableVertexAttribArray(4));
    CHECK_GL_ERROR(glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent)));
    // bone IDs
    CHECK_GL_ERROR(glEnableVertexAttribArray(5));
    CHECK_GL_ERROR(glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, boneIDs)));
    // bone weights
    CHECK_GL_ERROR(glEnableVertexAttribArray(6));
    CHECK_GL_ERROR (glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, weights)));
    

    CHECK_GL_ERROR(glBindVertexArray(0));
}