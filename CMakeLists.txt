cmake_minimum_required(VERSION 3.8)

project(roguelike CXX)

file(GLOB_RECURSE SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/tcod/include
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})


if (MSVC)
    target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/tcod/libtcod.lib)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/tcod/libtcod.so)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)
