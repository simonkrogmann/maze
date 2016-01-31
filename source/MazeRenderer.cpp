#include "MazeRenderer.h"

#include <glbinding/gl/gl.h>
#include <utilgpu/gl/Shader.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Maze.h"

using namespace gl;

MazeRenderer::MazeRenderer(std::unique_ptr<Maze> maze)
: m_maze{std::move(maze)}
{
}

MazeRenderer::~MazeRenderer()
{
}

void MazeRenderer::init()
{
    auto shader = util::Shader::fragment(util::File{"../source/shader/groundplane.frag"});
    m_groundPlane.addFragmentShader(shader);
}

void MazeRenderer::reload()
{

}

void MazeRenderer::saveFramebuffers()
{

}

void MazeRenderer::draw(const util::viewport::Viewport& viewport)
{
    auto view = glm::lookAt(glm::vec3(0.0, 0.0, 0.2), glm::vec3(0.0, 1.0, 0.2), glm::vec3(0.0, 0.0, 1.0));
    auto projection = glm::perspective(90.f, static_cast<float>(viewport.width / viewport.height), 0.1f, 100.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_groundPlane.setViewProjection(glm::value_ptr(projection* view));
    m_groundPlane.draw();
}
