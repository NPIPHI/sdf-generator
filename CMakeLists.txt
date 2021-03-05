cmake_minimum_required(VERSION 3.16)
project(ecs)

set(CMAKE_CXX_STANDARD 17)

add_executable(ecs src/main.cpp src/gfx/init.cpp src/gfx/init.hpp src/gfx/shader.cpp src/gfx/shader.hpp src/io/io.cpp src/io/io.hpp src/mainLoop.h src/App.cpp src/App.hpp src/gfx/bufferObject.h src/gfx/texture.cpp src/gfx/texture.hpp src/sdf/sdf.cpp src/sdf/sdf.h)

find_package(glm REQUIRED)

target_link_libraries(ecs glm)

if(EMSCRIPTEN)

    set(FLAGS "-s USE_GLFW=3 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s ENVIRONMENT=web --preload-file ../res/")

    set_target_properties(ecs PROPERTIES
            COMPILE_FLAGS ${FLAGS}
            LINK_FLAGS ${FLAGS}
            SUFFIX ".js"
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build
            )

else()
    find_package(OpenGL REQUIRED)
    find_package(glfw3 REQUIRED)
    find_package(GLEW REQUIRED)

    target_link_libraries(ecs
            ${OPENGL_LIBRARY}
            glfw
            GLEW::glew
            )
endif()