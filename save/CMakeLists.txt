project(ExtractSaveResource)

build_target(
  NAME
  extract_save
  TYPE
  ESMODULE
  VERSION
  1
  SOURCES
  extract_save.cpp
  LINKS
  spike-interface
  zlib-objects
  AUTHOR
  "Lukas Cone"
  DESCR
  "Extract resource from save"
  START_YEAR
  2023)

