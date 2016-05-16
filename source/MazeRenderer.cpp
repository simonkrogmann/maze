#include "MazeRenderer.h"

#include <glbinding/gl/gl.h>
#include <utilgpu/cpp/Group.h>
#include <utilgpu/cpp/file.h>
#include <utilgpu/gl/Model.h>
#include <utilgpu/gl/Program.h>
#include <utilgpu/gl/Shader.h>
#include <utilgpu/gl/Texture.h>
#include <utilgpu/gl/viewport.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

#include "Maze.h"
#include "MazeDrawable.h"

using namespace gl;

MazeRenderer::MazeRenderer(std::unique_ptr<Maze> maze) : m_maze{std::move(maze)}
{
    addDependentPath("../source/shader/groundplane.frag");
    addDependentPath("../source/shader/wall.vert");
    addDependentPath("../source/shader/wall.geom");
    addDependentPath("../source/shader/wall.frag");
    reload();
}

MazeRenderer::~MazeRenderer()
{
}

void MazeRenderer::init()
{
    m_mazeDrawable = MazeDrawable::generateFrom(m_maze.get());
}

void MazeRenderer::reload()
{
    util::Group<util::Shader> groundPlaneShaders(
        m_groundPlane.getVertexShader(),
        util::Shader::fragment(util::File{"../source/shader/groundplane.frag"},
                               {m_shadowMap.getShaderInclude()}));
    m_groundPlaneProgram = std::make_unique<util::Program>(groundPlaneShaders);

    util::Group<util::Shader> mazeShaders(
        util::Shader::vertex(util::File{"../source/shader/wall.vert"}),
        util::Shader::geometry(util::File{"../source/shader/wall.geom"}),
        util::Shader::fragment(util::File{"../source/shader/wall.frag"},
                               {m_shadowMap.getShaderInclude()}));
    m_mazeProgram = std::make_unique<util::Program>(mazeShaders);
}

void MazeRenderer::saveFramebuffers()
{
    m_shadowMap.get()->save("test.png");
}

void MazeRenderer::draw(const util::viewport::Viewport& viewport)
{
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_MULTISAMPLE);

    const auto lightView =
        glm::lookAt(glm::vec3(-2.0, 2.5, 2.0), glm::vec3(0.0, 2.6, 2.0),
                    glm::vec3(0.0, 0.0, 1.0));
    const auto lightProjection = glm::perspective(2.0f, 1.0f, 0.1f, 50.f);
    std::vector<util::Model> models;
    models.push_back({m_mazeDrawable.get(), glm::mat4{}});
    m_shadowMap.draw(models, lightProjection * lightView);

    const auto view =
        glm::lookAt(glm::vec3(-1.5, -1.5, 2), glm::vec3(0.0, 0.0, 2),
                    glm::vec3(0.0, 0.0, 1.0));
    const auto projection = glm::perspective(
        1.1f, static_cast<float>(viewport.width) / viewport.height, 0.1f,
        100.f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const auto program : {m_groundPlaneProgram.get(), m_mazeProgram.get()})
    {
        assert(program->isLinked());
        program->use();
        glActiveTexture(GL_TEXTURE0);
        m_shadowMap.get()->bind();
        glUniform1i((*program)["shadowmap"], 0);
        glUniformMatrix4fv((*program)["lightViewProjection"], 1, GL_FALSE,
                           glm::value_ptr(lightProjection * lightView));
        glUniformMatrix4fv((*program)["viewProjection"], 1, GL_FALSE,
                           glm::value_ptr(projection * view));
    }

    m_groundPlaneProgram->use();
    m_groundPlane.draw();
    m_mazeProgram->use();
    m_mazeDrawable->draw();
    glDisable(GL_DEPTH_TEST);
}
