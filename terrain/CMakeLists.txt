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

