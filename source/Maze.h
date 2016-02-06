#pragma once

#include <cstddef>
#include <vector>

#include <glm/vec2.hpp>

enum Direction
{
    horizontal,
    vertical
};

struct Wall
{
    glm::vec2 start;
    glm::vec2 direction;
};

class Maze
{
public:
    Maze(const int& size = 100);
    ~Maze();

    std::vector<Wall> walls() const;
    std::vector<Wall> wallEnds() const;
    bool hasWallAround(const int& x, const int& y) const;
    bool isWall(const int& x, const int& y, Direction direction) const;

    int size() const;

private:
    std::vector<std::vector<bool>> m_wallsX;
    std::vector<std::vector<bool>> m_wallsY;
    int m_size;
};
