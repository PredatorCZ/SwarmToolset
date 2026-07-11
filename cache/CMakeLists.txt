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
  stcache-interface
  AUTHOR
  "Lukas Cone"
  DESCR
  "Create stgame mod cache"
  START_YEAR
  2023)
