#include "MazeRenderer.h"

#include "Maze.h"

MazeRenderer::MazeRenderer(std::unique_ptr<Maze> maze)
: m_maze{std::move(maze)}
{
}

MazeRenderer::~MazeRenderer()
{
}

void MazeRenderer::init()
{

}

void MazeRenderer::reload()
{

}

void MazeRenderer::saveFramebuffers()
{

}

void MazeRenderer::draw(const util::viewport::Viewport& viewport)
{

}
