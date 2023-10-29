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
  spike-interface
  gltf-interface
  libswarm
  zstd-objects
  AUTHOR
  "Lukas Cone"
  DESCR
  "Convert Swarm Binary Model to GLTF"
  START_YEAR
  2017)

