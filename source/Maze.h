#pragma once

#include <cstddef>
#include <vector>

#include <glm/vec2.hpp>

struct WallSlot
{
    glm::vec2 start;
    glm::vec2 end;
    bool isWall;
};

class Maze
{
public:
    Maze(const size_t& size = 100);
    ~Maze();

    std::vector<WallSlot> walls();

private:
    std::vector<std::vector<bool>> m_wallsX;
    std::vector<std::vector<bool>> m_wallsY;
};
