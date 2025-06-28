add_executable(script_editor script_editor.cpp debug.cpp language.cpp)

target_link_libraries(script_editor PUBLIC gui ImGui squirrel_static sqstdlib_static sqigui_static spike-objects pugixml-objects)
