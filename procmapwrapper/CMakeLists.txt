project(integers_bytes)

cmake_minimum_required(VERSION 3.18)

enable_testing ()

include (CTest)

add_subdirectory(conversion)

add_subdirectory(conversiontests)

add_subdirectory(mapsparser)

add_subdirectory(mapsparsertests)

add_subdirectory(mapsreader)

add_subdirectory(procmapwrapper)
