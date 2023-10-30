project(SBM2GLTF)

build_target(
  NAME
  sbm_to_gltf
  TYPE
  ESMODULE
  VERSION
  1
  SOURCES
  sbm_to_gltf.cpp
  LINKS
  gltf-interface
  libswarm
  AUTHOR
  "Lukas Cone"
  DESCR
  "Convert Swarm Binary Model to GLTF"
  START_YEAR
  2017)

