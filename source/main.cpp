#include <memory>

#include <utilgpu/cpp/str.h>
#include <utilgpu/gl/Shader.h>
#include <utilgpu/gl/base.h>
#include <utilgpu/qt/Config.h>
#include <utilgpu/window/Window.h>

#include "Maze.h"
#include "MazeRenderer.h"

int main(int argc, char* argv[])
{
    std::string applicationName = "maze";
    util::Config config{"simonkrogmann", applicationName};
    config.setDefaults({
        {"gl-version", "best"},
        {"fullscreen", "false"},
    });
    config.load(argc, argv);

    util::Window w;

    const auto version = config.value("gl-version");
    if (version != "best")
    {
        const auto numbers = util::splitNumbers(version, ".");
        w.requestGLVersion(numbers.first, numbers.second);
    }
    w.MSAASamples(4);
    w.init(applicationName, config.value<bool>("fullscreen"));
    util::glInitialize(util::getGLProcAddressPointer());
    util::glContextInfo();
    w.initAfterGL();

    auto renderer = std::make_unique<MazeRenderer>(std::make_unique<Maze>());
    w.setRenderer(std::move(renderer));
    w.loop();

    return 0;
}
