#pragma once

#include <vector>

#include <utilgpu/gl/GroundPlane.h>
#include <utilgpu/gl/Renderer.h>
#include <utilgpu/gl/ShadowMap.h>

class Maze;
class MazeDrawable;

namespace util
{
class Program;
}

class MazeRenderer : public util::Renderer
{
public:
    MazeRenderer(std::unique_ptr<Maze> maze);
    ~MazeRenderer();

    virtual void init() override;
    virtual void reload() override;
    virtual void saveFramebuffers() override;

protected:
    virtual void draw(const util::viewport::Viewport& viewport) override;

private:
    std::unique_ptr<Maze> m_maze;
    util::GroundPlane m_groundPlane;
    std::unique_ptr<MazeDrawable> m_mazeDrawable;
    std::unique_ptr<util::Program> m_groundPlaneProgram;
    std::unique_ptr<util::Program> m_mazeProgram;
    util::ShadowMap m_shadowMap;
};
