cmake_minimum_required(VERSION 3.3)

set(CMAKE_CXX_STANDARD 20)

project(SwarmToolset)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

option(CLI "" ON)
option(GLTF "" ON)
set(EXPOSE_SYMBOLS spike;pugixml;gltf)

set(TPD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party)

add_subdirectory(${TPD_PATH}/spike)
include(version)
#toolset_version()

set_target_properties(spike_cli PROPERTIES OUTPUT_NAME swarm_toolset)

add_library(libswarm OBJECT src/terrain.cpp src/material.cpp src/stcache.cpp src/script_reflect0.cpp src/script_reflect1.cpp src/script_reflect2.cpp src/script.cpp src/model.cpp)
target_link_libraries(libswarm spike-interface)
target_include_directories(libswarm PUBLIC include)
set_target_properties(libswarm PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

file(GLOB ZLIB_SOURCES "${TPD_PATH}/zlib/*.c")
add_library(zlib-objects OBJECT ${ZLIB_SOURCES})
set_target_properties(zlib-objects PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

enable_language(ASM)
file(GLOB_RECURSE ZSTD_SOURCE_FILES "${TPD_PATH}/zstd/lib/*.c")
add_library(zstd-objects OBJECT ${ZSTD_SOURCE_FILES} ${TPD_PATH}/zstd/lib/decompress/huf_decompress_amd64.S)
set_target_properties(zstd-objects PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
target_include_directories(zstd-objects PUBLIC ${TPD_PATH}/zstd/lib/common ${TPD_PATH}/zstd/lib)

add_spike_subdir(slack)
add_spike_subdir(material)
add_spike_subdir(terrain)
add_spike_subdir(cache)
add_spike_subdir(save)
add_spike_subdir(scripts)
add_spike_subdir(model)

if (NOT ${CMAKE_BUILD_TYPE} STREQUAL Release)
  add_spike_subdir(dev)
endif()

add_subdirectory(launcher)
