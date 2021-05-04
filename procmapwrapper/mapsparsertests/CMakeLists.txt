add_executable(mapsparsertests tests.cpp)

set_property(TARGET mapsparsertests PROPERTY CXX_STANDARD 20)

target_include_directories(mapsparsertests PRIVATE ../mapsparser ../outsideincludes)

target_link_libraries(mapsparsertests PRIVATE mapsparser)

add_test(NAME mapsparsertests COMMAND mapsparsertests)
