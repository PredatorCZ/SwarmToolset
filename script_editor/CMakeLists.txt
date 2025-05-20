
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(GLEW REQUIRED)

add_executable(script_editor script_editor.cpp debug.cpp language.cpp)

target_link_libraries(script_editor PUBLIC glfw OpenGL::GL GLEW::GLEW ImGui squirrel_static sqstdlib_static sqigui_static spike-objects pugixml-objects)
