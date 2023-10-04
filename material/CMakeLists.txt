project(FixupMaterials)

build_target(
  NAME
  fixup_materials
  TYPE
  ESMODULE
  VERSION
  1
  SOURCES
  fixup_materials.cpp
  LINKS
  spike-interface
  libswarm
  AUTHOR
  "Lukas Cone"
  DESCR
  "Fixup SB textures"
  START_YEAR
  2017)

project(FixupMaterials)

build_target(
  NAME
  dump_materials
  TYPE
  ESMODULE
  VERSION
  1
  SOURCES
  dump_materials.cpp
  LINKS
  spike-interface
  pugixml-interface
  libswarm
  AUTHOR
  "Lukas Cone"
  DESCR
  "Dump SB textures"
  START_YEAR
  2017)
