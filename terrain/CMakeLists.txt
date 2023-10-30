project(DumpSignature)

build_target(
  NAME
  dump_signature
  TYPE
  ESMODULE
  VERSION
  1
  SOURCES
  dump_signature.cpp
  INCLUDES
  ${TPD_PATH}/spike/3rd_party/json
  LINKS
  spike-interface
  AUTHOR
  "Lukas Cone"
  DESCR
  "Dump SBT signature"
  START_YEAR
  2017)

project(SBT2GLTF)

build_target(
  NAME
  sbt_to_gltf
  TYPE
  ESMODULE
  VERSION
  1
  SOURCES
  sbt_to_gltf.cpp
  LINKS
  gltf-interface
  libswarm
  AUTHOR
  "Lukas Cone"
  DESCR
  "Convert Swarm Binary Terrain to GLTF"
  START_YEAR
  2017)

