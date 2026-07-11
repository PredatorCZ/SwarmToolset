cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 20)

project(SwarmToolset)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

option(EDITORS "Build GUI editors" ON)
option(MODS "Build mod framework" ON)
option(CLI "" ON)
option(GLTF "" ON)
set(EXPOSE_SYMBOLS spike;pugixml;gltf;libswarm;stcache)

set(TPD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party)

add_subdirectory(${TPD_PATH}/spike)
include(version)
toolset_version()

set_target_properties(spike_cli PROPERTIES OUTPUT_NAME swarm_toolset)

add_library(libswarm-interface INTERFACE)
target_link_libraries(libswarm-interface INTERFACE spike-interface)
target_include_directories(libswarm-interface INTERFACE include)

add_library(libswarm-objects OBJECT src/terrain.cpp src/material.cpp src/script_reflect0.cpp src/script_reflect1.cpp src/script_reflect2.cpp src/script.cpp src/model.cpp)
target_link_libraries(libswarm-objects libswarm-interface)
set_target_properties(libswarm-objects PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
target_expose_defs(libswarm SW_EXPORT SW_IMPORT)

set(CMAKE_BUILD_TYPE_BAK ${CMAKE_BUILD_TYPE})
set(CMAKE_BUILD_TYPE Release)

file(GLOB ZLIB_SOURCES "${TPD_PATH}/zlib/*.c")
add_library(zlib-objects OBJECT ${ZLIB_SOURCES})
target_include_directories(zlib-objects PUBLIC ${TPD_PATH}/zlib)
set_target_properties(zlib-objects PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

enable_language(ASM)
file(GLOB_RECURSE ZSTD_SOURCE_FILES "${TPD_PATH}/zstd/lib/*.c")
add_library(zstd-objects OBJECT ${ZSTD_SOURCE_FILES} ${TPD_PATH}/zstd/lib/decompress/huf_decompress_amd64.S)
target_include_directories(zstd-objects PRIVATE ${TPD_PATH}/zstd/lib/common PUBLIC ${TPD_PATH}/zstd/lib)
set_target_properties(zstd-objects PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_BAK})

add_library(stcache-interface INTERFACE)
target_link_libraries(stcache-interface INTERFACE spike-interface)
target_include_directories(stcache-interface INTERFACE include)

add_library(stcache-objects OBJECT src/stcache.cpp)
target_link_libraries(stcache-objects PUBLIC stcache-interface)
target_link_libraries(stcache-objects LINK_PUBLIC zstd-objects)
set_target_properties(stcache-objects PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
target_expose_defs(stcache SW_EXPORT SW_IMPORT)

target_link_libraries(spike_cli stcache-objects libswarm-objects zstd-objects)

if(EDITORS)

add_subdirectory(${TPD_PATH}/veverka)
add_subdirectory(${TPD_PATH}/imgui)

add_subdirectory(gui)
add_subdirectory(script_editor)

add_subdirectory(data_editor)

endif()

if(MODS)
  add_spike_subdir(cache)
  add_subdirectory(launcher)
endif()

add_spike_subdir(slack)
add_spike_subdir(material)
add_spike_subdir(terrain)
add_spike_subdir(save)
add_spike_subdir(scripts)
add_spike_subdir(model)
add_spike_subdir(anim)

if (NOT ${CMAKE_BUILD_TYPE} STREQUAL Release)
  add_spike_subdir(dev)
endif()

#add_subdirectory(engine)
