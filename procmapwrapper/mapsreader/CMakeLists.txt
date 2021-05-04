add_library(mapsreader STATIC mapsreader.cpp)

set_property(TARGET mapsreader PROPERTY CXX_STANDARD 20)

target_include_directories(mapsreader PRIVATE ../mapsparser)

target_link_libraries(mapsreader PRIVATE mapsparser)
