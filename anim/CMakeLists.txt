project(SBA2GLTF)

build_target(
  NAME
  sba_to_gltf
  TYPE
  ESMODULE
  VERSION
  1
  SOURCES
  sba_to_gltf.cpp
  LINKS
  gltf-interface
  libswarm
  AUTHOR
  "Lukas Cone"
  DESCR
  "Convert Swarm Binary Animation to GLTF"
  START_YEAR
  2017)

