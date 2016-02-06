#pragma once

#include <vector>
#include <memory>

#include <utilgpu/gl/Drawable.h>
#include <glm/mat4x4.hpp>

class Maze;

class MazeDrawable : public util::Drawable
{
public:
    static std::unique_ptr<MazeDrawable> generateFrom(const Maze* maze);

    MazeDrawable(const std::vector<glm::vec3>& vertices);
    virtual ~MazeDrawable();

    virtual void draw() override;

private:
    unsigned int m_number = 1;
};
