project(SLAKExtract)

build_target(
  NAME
  extract_slak
  TYPE
  ESMODULE
  VERSION
  1
  SOURCES
  extract_slak.cpp
  LINKS
  spike-interface
  zlib-objects
  libswarm
  INCLUDES
  ${TPD_PATH}/zlib
  AUTHOR
  "Lukas Cone"
  DESCR
  "SLAK Archive Extractor"
  START_YEAR
  2017)

project(SLAKCreate)

build_target(
  NAME
  create_slak
  TYPE
  ESMODULE
  VERSION
  1
  SOURCES
  create_slak.cpp
  LINKS
  spike-interface
  zlib-objects
  libswarm
  INCLUDES
  ${TPD_PATH}/zlib
  AUTHOR
  "Lukas Cone"
  DESCR
  "Create SLAK Archive"
  START_YEAR
  2017)

