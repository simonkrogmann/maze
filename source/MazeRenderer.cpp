#include "MazeRenderer.h"

#include <glbinding/gl/gl.h>
#include <utilgpu/gl/Program.h>
#include <utilgpu/gl/Shader.h>
#include <utilgpu/cpp/Group.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Maze.h"
#include "MazeDrawable.h"

using namespace gl;

MazeRenderer::MazeRenderer(std::unique_ptr<Maze> maze) : m_maze{std::move(maze)}
{
    addDependentPath({"../source/shader/groundplane.frag"});
    addDependentPath({"../source/shader/wall.vert"});
    addDependentPath({"../source/shader/wall.geom"});
    addDependentPath({"../source/shader/wall.frag"});
    reload();
}

MazeRenderer::~MazeRenderer()
{
}

void MazeRenderer::init()
{
    for (const auto& wallSlot : m_maze->walls())
    {
        glm::mat4 model;
        auto wallVector = wallSlot.end - wallSlot.start;
        model = glm::translate(model, glm::vec3(wallSlot.start, 0.0f));
        model = glm::rotate(model, -std::atan2(wallVector.y, wallVector.x),
                            glm::vec3(0.0f, 0.0f, 1.0f));
        model =
            glm::scale(model, glm::vec3(1.0f, glm::length(wallVector), 1.0f));
        m_models.push_back({model, wallSlot.isWall});
    }
    m_mazeDrawable = std::make_unique<MazeDrawable>(m_models);
}

void MazeRenderer::reload()
{
    auto shader =
        util::Shader::fragment(util::File{"../source/shader/groundplane.frag"});
    m_groundPlane.addFragmentShader(shader);

    util::Group<util::Shader> shaders(
        util::Shader::vertex(util::File{"../source/shader/wall.vert"}),
        util::Shader::geometry(util::File{"../source/shader/wall.geom"}),
        util::Shader::fragment(util::File{"../source/shader/wall.frag"}));
    m_mazeProgram = std::make_unique<util::Program>(shaders);
}

void MazeRenderer::saveFramebuffers()
{
}

void MazeRenderer::draw(const util::viewport::Viewport& viewport)
{
    glEnable(GL_DEPTH_TEST);
    auto view = glm::lookAt(glm::vec3(-1.0, -1.0, 2), glm::vec3(0.0, 0.0, 2),
                            glm::vec3(0.0, 0.0, 1.0));
    auto projection = glm::perspective(
        89.f, static_cast<float>(viewport.width) / viewport.height, 0.1f,
        100.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_groundPlane.setViewProjection(glm::value_ptr(projection * view));
    m_groundPlane.draw();
    m_mazeProgram->use();
    glUniformMatrix4fv((*m_mazeProgram)["viewProjection"], 1, GL_FALSE,
                       glm::value_ptr(projection * view));
    m_mazeDrawable->draw();
    glDisable(GL_DEPTH_TEST);
}
