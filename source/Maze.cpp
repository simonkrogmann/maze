#include "Maze.h"

#include <random>

Maze::Maze(const size_t& size)
    : m_wallsX{size, std::vector<bool>(size + 1, -1)}
    , m_wallsY{size + 1, std::vector<bool>(size, -1)}
    , m_size{size}
{
    std::default_random_engine generator;
    std::bernoulli_distribution distribution(0.5);

    for (auto& row : m_wallsX)
    {
        for (auto&& cell : row)
        {
            cell = distribution(generator);
        }
    }
    for (auto& row : m_wallsY)
    {
        for (auto&& cell : row)
        {
            cell = distribution(generator);
        }
    }
}

std::vector<Wall> Maze::walls() const
{
    std::vector<Wall> result;
    for (size_t x = 0; x < size(); ++x)
    {
        for (size_t y = 0; y < size() + 1; ++y)
        {
            if (isWall(x, y, horizontal))
            {
                result.push_back({{x, y}, {1, 0}});
            }
        }
    }
    for (size_t x = 0; x < m_wallsY.size(); ++x)
    {
        for (size_t y = 0; y < m_wallsY[x].size(); ++y)
        {
            if (isWall(x, y, vertical))
            {
                result.push_back({{x, y}, {0, 1}});
            }
        }
    }
    return result;
}

bool Maze::hasWallAround(const int& x, const int& y) const
{
    return isWall(x, y, horizontal) || isWall(x - 1, y, horizontal) ||
           isWall(x, y, vertical) || isWall(x, y - 1, vertical);
}

bool Maze::isWall(const int& x, const int& y, Direction direction) const
{
    if (size() < 1)
    {
        return false;
    }
    auto& walls = (direction == horizontal) ? m_wallsX : m_wallsY;
    if (x < 0 || y < 0 || x >= static_cast<int>(walls.size()) ||
        y >= static_cast<int>(walls[0].size()))
    {
        return false;
    }
    return walls[x][y];
}

std::vector<Wall> Maze::wallEnds() const
{
    std::vector<Wall> result;
    for (size_t y = 0; y < size() + 1; ++y)
    {
        for (size_t x = 0; x < size() + 1; ++x)
        {
            if (hasWallAround(x, y))
            {
                if (!isWall(x, y, horizontal))
                {
                    result.push_back({{x, y}, {1, 0}});
                }
                if (!isWall(x, y, vertical))
                {
                    result.push_back({{x, y}, {0, 1}});
                }
                if (!isWall(x - 1, y, horizontal))
                {
                    result.push_back({{x, y}, {-1, 0}});
                }
                if (!isWall(x, y - 1, vertical))
                {
                    result.push_back({{x, y}, {0, -1}});
                }
            }
        }
    }
    return result;
}

Maze::~Maze() {}

size_t Maze::size() const
{
    return m_size;
}
