#pragma once

#include <memory>
#include <vector>

#include <utilgpu/gl/Drawable.h>
#include <glm/fwd.hpp>

class Maze;

class MazeDrawable : public util::Drawable
{
public:
    static std::unique_ptr<MazeDrawable> generateFrom(const Maze* maze);

    MazeDrawable(const std::vector<glm::vec3>& vertices);
    virtual ~MazeDrawable();

    virtual void draw() override;

private:
    size_t m_number = 1;
};
