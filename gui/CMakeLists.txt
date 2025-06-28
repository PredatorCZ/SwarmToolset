
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(GLEW REQUIRED)

add_library(gui OBJECT window.cpp widgets.cpp)

target_link_libraries(gui PUBLIC glfw PUBLIC OpenGL::GL PUBLIC GLEW::GLEW PUBLIC ImGui )
target_include_directories(gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
