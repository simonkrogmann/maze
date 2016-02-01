#include "MazeDrawable.h"

#include <vector>

#include <glbinding/gl/gl.h>
#include <glm/vec3.hpp>

using namespace gl;

MazeDrawable::MazeDrawable(
    const std::vector<std::pair<glm::mat4, bool>>& models)
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    std::vector<glm::vec3> verticesWall = {
        {0.05, 0.05, 0},  {0.05, 0.05, 1},  {0.05, 0.95, 0},  {0.05, 0.95, 0},
        {0.05, 0.05, 1},  {0.05, 0.95, 1},  {-0.05, 0.05, 0}, {-0.05, 0.95, 0},
        {-0.05, 0.05, 1}, {-0.05, 0.05, 1}, {-0.05, 0.95, 0}, {-0.05, 0.95, 1},
        {0.05, 0.05, 1},  {-0.05, 0.05, 1}, {0.05, 0.95, 1},  {-0.05, 0.05, 1},
        {-0.05, 0.95, 1}, {0.05, 0.95, 1},
    };

    std::vector<glm::vec3> verticesNoWall = {
        {-0.05, 0.05, 0}, {0.05, 0.05, 0}, {-0.05, 0.05, 1}, {0.05, 0.05, 1},
        {-0.05, 0.05, 1}, {0.05, 0.05, 0}, {-0.05, 0.95, 0}, {-0.05, 0.95, 1},
        {0.05, 0.95, 0},  {0.05, 0.95, 0}, {-0.05, 0.95, 1}, {0.05, 0.95, 1},
    };

    std::vector<glm::vec3> verticesAll = {
        {-0.05, 0.05, 1}, {0.05, 0.05, 1},  {0, 0, 1},
        {0.05, 0.95, 1},  {-0.05, 0.95, 1}, {0, 1, 1},
    };

    GLuint buffer;

    std::vector<glm::vec3> vertices = {};
    for (const auto& model : models)
    {
        const auto& geometry = model.second ? verticesWall : verticesNoWall;
        for (const auto& vertex : geometry)
        {
            auto new_vertex = model.first * glm::vec4(vertex, 1.0f);
            new_vertex /= new_vertex.w;
            glm::vec3 new_vertex3{new_vertex};
            vertices.push_back(new_vertex3);
        }
        for (const auto& vertex : verticesAll)
        {
            auto new_vertex = model.first * glm::vec4(vertex, 1.0f);
            new_vertex /= new_vertex.w;
            glm::vec3 new_vertex3{new_vertex};
            vertices.push_back(new_vertex3);
        }
    }
    m_number = vertices.size();

    glGenBuffers(1, &buffer);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3),
                 vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glDeleteBuffers(1, &buffer);
}

MazeDrawable::~MazeDrawable()
{
    glDeleteVertexArrays(1, &m_vao);
}

void MazeDrawable::draw()
{
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_number);
    glBindVertexArray(0);
}
