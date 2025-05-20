set(SQSIGUI_SRC
  data_types.cpp
  drawlist.cpp)

# if(NOT DISABLE_DYNAMIC)
#   add_library(sqigui SHARED ${SQSIGUI_SRC})
#   add_library(squirrel::sqigui ALIAS sqigui)
#   set_property(TARGET sqigui PROPERTY EXPORT_NAME sqigui)
#   target_link_libraries(sqigui squirrel ImGui)
#   if(NOT SQ_DISABLE_INSTALLER)
#     install(TARGETS sqigui EXPORT squirrel
#       RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Libraries
#       LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Libraries NAMELINK_SKIP
#       ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Libraries
#       )
#     install(TARGETS sqigui EXPORT squirrel
#       LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development NAMELINK_ONLY
#       )
#   endif()
#   target_include_directories(sqigui PUBLIC
#     "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
#     "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
#     )
# endif()

if(NOT DISABLE_STATIC)
  add_library(sqigui_static STATIC ${SQSIGUI_SRC})
  add_library(squirrel::sqigui_static ALIAS sqigui_static)
  target_link_libraries(sqigui_static squirrel ImGui)
  set_property(TARGET sqigui_static PROPERTY EXPORT_NAME sqigui_static)
  if(NOT SQ_DISABLE_INSTALLER)
    install(TARGETS sqigui_static EXPORT squirrel ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development)
  endif()
  target_include_directories(sqigui_static PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    )
endif()

if(LONG_OUTPUT_NAMES)
  if(NOT DISABLE_STATIC)
    set_target_properties(sqigui_static PROPERTIES OUTPUT_NAME sqigui3_static)
  endif()
endif()
