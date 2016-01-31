#pragma once

#include <utilgpu/gl/Renderer.h>

class Maze;

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
};
