cmake_minimum_required(VERSION 3.3)

project(StgameCache)

build_target(
  NAME
  make_cache
  TYPE
  ESMODULE
  SOURCES
  make_cache.cpp
  VERSION
  1
  LINKS
  spike-interface
  zstd-objects
  libswarm
  AUTHOR
  "Lukas Cone"
  DESCR
  "Create stgame mod cache"
  START_YEAR
  2023)
