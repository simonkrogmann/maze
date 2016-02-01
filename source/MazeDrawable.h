#pragma once

#include <vector>

#include <utilgpu/gl/Drawable.h>
#include <glm/mat4x4.hpp>

class MazeDrawable : public util::Drawable
{
public:
    MazeDrawable(const std::vector<std::pair<glm::mat4, bool>>& models);
    virtual ~MazeDrawable();

    virtual void draw() override;

private:
    std::vector<unsigned char> m_indices;
    unsigned int m_number = 1;
};
