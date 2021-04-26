add_executable(conversiontests tests.cpp)

set_property(TARGET conversiontests PROPERTY CXX_STANDARD 20)

target_include_directories(conversiontests PRIVATE ../conversion)

target_link_libraries(conversiontests PRIVATE conversion)

add_test(NAME conversiontests COMMAND conversiontests)
