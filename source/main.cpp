#include <memory>

#include <utilgpu/qt/Config.h>
#include <utilgpu/gl/base.h>
#include <utilgpu/gl/Shader.h>
#include <utilgpu/cpp/str.h>
#include <utilgpu/window/Window.h>

#include "MazeRenderer.h"
#include "Maze.h"

int main(int argc, char* argv[])
{
    util::Config config{"simonkrogmann", "procedural-viewer"};
    config.setDefaults({
        {"gl-version", "best"}, {"fullscreen", "false"},
    });
    config.load(argc, argv);

    util::Shader::id = config.valueUInt("shader-id") + 100;
    config.setValue("shader-id", util::Shader::id);

    util::Window w;

    const auto version = config.value("gl-version");
    if (version != "best")
    {
        const auto numbers = util::splitNumbers(version, ".");
        w.requestGLVersion(numbers.first, numbers.second);
    }
    w.init("procedural-viewer", config.value("fullscreen") == "true");
    util::glInitialize();
    util::glContextInfo();
    w.initAfterGL();

    auto renderer = std::make_unique<MazeRenderer>(std::make_unique<Maze>());
    w.setRenderer(std::move(renderer));
    w.loop();

    config.setValue("shader-id", util::Shader::id);
    return 0;
}
