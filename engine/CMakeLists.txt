
add_library(tnl OBJECT tnl/tnl/assert.cpp)
target_include_directories(tnl PUBLIC tnl/tnl)
target_compile_definitions(tnl PUBLIC i386 TNL_GCC_3)

add_library(swarm OBJECT
src/sl_variable_abstract_ref.cpp
)

target_include_directories(swarm PUBLIC include)
target_link_libraries(swarm tnl)
