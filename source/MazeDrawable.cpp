#include "MazeDrawable.h"

#include <vector>

#include <glbinding/gl/gl.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Maze.h"

using namespace gl;

MazeDrawable::MazeDrawable(const std::vector<glm::vec3>& vertices)
    : m_number{vertices.size()}
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    GLuint buffer;
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

std::unique_ptr<MazeDrawable> MazeDrawable::generateFrom(const Maze* maze)
{
    auto walls = maze->walls();
    auto wallEnds = maze->wallEnds();
    std::vector<std::pair<Wall, bool>> wallObjects;
    for (const auto& wall : maze->walls())
    {
        wallObjects.push_back({wall, true});
    }
    for (const auto& wallEnd : maze->wallEnds())
    {
        wallObjects.push_back({wallEnd, false});
    }
    std::vector<std::pair<glm::mat4, bool>> models;
    for (const auto& pair : wallObjects)
    {
        const auto& wallObject = pair.first;
        glm::mat4 model;
        model = glm::translate(model, glm::vec3(wallObject.start, 0.0f));
        model = glm::rotate(
            model, -std::atan2(wallObject.direction.x, wallObject.direction.y),
            glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(
            model, glm::vec3(1.0f, glm::length(wallObject.direction), 1.0f));
        models.push_back({model, pair.second});
    }

    std::vector<glm::vec3> verticesWall = {
        {0.05, 0.05, 0},  {0.05, 0.05, 1},  {0.05, 0.95, 0},
        {0.05, 0.95, 0},  {0.05, 0.05, 1},  {0.05, 0.95, 1},  // side 1
        {-0.05, 0.05, 0}, {-0.05, 0.95, 0}, {-0.05, 0.05, 1},
        {-0.05, 0.05, 1}, {-0.05, 0.95, 0}, {-0.05, 0.95, 1},  // side 2
        {0.05, 0.05, 1},  {-0.05, 0.05, 1}, {0.05, 0.95, 1},
        {-0.05, 0.05, 1}, {-0.05, 0.95, 1}, {0.05, 0.95, 1},  // top
        {-0.05, 0.05, 1}, {0.05, 0.05, 1},  {0, 0, 1},
        {0.05, 0.95, 1},  {-0.05, 0.95, 1}, {0, 1, 1},
    };

    std::vector<glm::vec3> verticesWallEnd = {
        {-0.05, 0.05, 0}, {0.05, 0.05, 0},  {-0.05, 0.05, 1},
        {0.05, 0.05, 1},  {-0.05, 0.05, 1}, {0.05, 0.05, 0}, // side
        {-0.05, 0.05, 1}, {0.05, 0.05, 1},  {0, 0, 1},
    };

    std::vector<glm::vec3> vertices = {};
    for (const auto& model : models)
    {
        const auto& geometry = model.second ? verticesWall : verticesWallEnd;
        for (const auto& vertex : geometry)
        {
            auto new_vertex = model.first * glm::vec4(vertex, 1.0f);
            new_vertex /= new_vertex.w;
            glm::vec3 new_vertex3{new_vertex};
            vertices.push_back(new_vertex3);
        }
    }
    return std::make_unique<MazeDrawable>(vertices);
}
