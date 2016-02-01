set(target maze)

set(sources
    main.cpp
    MazeRenderer.cpp
    Maze.cpp
    MazeDrawable.cpp
)

set(includes
    MazeRenderer.h
    Maze.h
    MazeDrawable.h
)

set(resources
)

set(libraries
    glbinding::glbinding
    utilgpu::cpp utilgpu::gl utilgpu::qt utilgpu::window
)

create_executable(${project} ${target} "${sources}" "${includes}" "${libraries}")
target_include_directories(${target} PUBLIC ${GLM_INCLUDE_DIRECTORIES})
generate_resource_header(${project} ${target} "${resources}")
