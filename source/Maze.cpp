#include "Maze.h"

#include <random>

Maze::Maze(const size_t& size)
    : m_wallsX{size + 1, std::vector<bool>(size, -1)}
    , m_wallsY{size + 1, std::vector<bool>(size, -1)}
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

std::vector<WallSlot> Maze::walls()
{
    std::vector<WallSlot> result;
    for (int y = 0; y < m_wallsX.size(); ++y)
    {
        for (int x = 0; x < m_wallsX[y].size(); ++x)
        {
            result.push_back({{x, y}, {x + 1, y}, m_wallsX[y][x]});
        }
    }
    for (int x = 0; x < m_wallsY.size(); ++x)
    {
        for (int y = 0; y < m_wallsX[x].size(); ++y)
        {
            result.push_back({{x, y}, {x, y + 1}, m_wallsY[x][y]});
        }
    }
    return result;
}

Maze::~Maze()
{
}
