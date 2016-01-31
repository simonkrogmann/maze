#pragma once

#include <vector>

class Maze
{
public:
    Maze();
    ~Maze();

private:
    std::vector<std::vector<int>> m_data;
};
