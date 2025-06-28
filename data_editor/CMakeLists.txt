add_executable(data_editor data_editor.cpp)

target_link_libraries(data_editor PUBLIC gui libswarm spike-objects pugixml-objects ImGui)
