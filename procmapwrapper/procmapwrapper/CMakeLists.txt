add_executable(procmapwrapper main.cpp)

set_property(TARGET procmapwrapper PROPERTY CXX_STANDARD 20)

target_include_directories(procmapwrapper PRIVATE ../mapsreader ../conversion ../mapsparser)

target_link_libraries(procmapwrapper PRIVATE mapsreader conversion)
