add_library(mapsparser STATIC mapparser.cpp utility.cpp mapregion.cpp)

set_property(TARGET mapsparser PROPERTY CXX_STANDARD 20)
