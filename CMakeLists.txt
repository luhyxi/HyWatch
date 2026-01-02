cmake_minimum_required(VERSION 3.23)

project(hywatch)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB_RECURSE sources
        "${CMAKE_SOURCE_DIR}/src/*.c"
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
        )

add_definitions(-DSOME_DEFINITION)

add_executable(hywatch ${sources})

target_include_directories(hywatch PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
