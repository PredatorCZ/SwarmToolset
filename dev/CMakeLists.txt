cmake_minimum_required(VERSION 3.3)

project(VirtualSlak)

build_target(
  NAME
  virtual_slak
  TYPE
  APP
  SOURCES
  virtual_slak.cpp
  LINKS
  spike-objects
  pugixml-objects
  stcache
  AUTHOR
  "Lukas Cone"
  DESCR
  "Create virtual slak from mod caches"
  START_YEAR
  2023)

project(ExtractCache)

build_target(
  NAME
  extract_cache
  TYPE
  ESMODULE
  SOURCES
  extract_cache.cpp
  VERSION
  1
  LINKS
  stcache
  AUTHOR
  "Lukas Cone"
  DESCR
  "Dump stgame mod cache"
  START_YEAR
  2023)

project(ValidatePatchedCache)

build_target(
  NAME
  validate_patched_cache
  TYPE
  APP
  SOURCES
  validate_patched_cache.cpp
  LINKS
  spike-objects
  pugixml-objects
  stcache
  AUTHOR
  "Lukas Cone"
  DESCR
  "Dump patched mod cache"
  START_YEAR
  2023)
