#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "integerconversion.h"

TEST_CASE( "integeralandfloat_tobytes_viceversa", "conversion" ) {
  SECTION( "int16tobytes" ) {
    std::vector<unsigned char> Bytes;
    append_integralorfloat_to_ubytesvector<int16_t>(Bytes, 1000);
    REQUIRE(Bytes.size() == 2);
    REQUIRE(Bytes.at(0) == 232);
    REQUIRE(Bytes.at(1) == 3);
  }
  SECTION( "int32tobytes" ) {
    std::vector<unsigned char> Bytes;
    append_integralorfloat_to_ubytesvector<int32_t>(Bytes, -90000000);
    REQUIRE(Bytes.size() == 4);
    REQUIRE(Bytes.at(0) == 128);
    REQUIRE(Bytes.at(1) == 181);
    REQUIRE(Bytes.at(2) == 162);
    REQUIRE(Bytes.at(3) == 250);
  }
  SECTION( "float32tobytes") {
    std::vector<unsigned char> bytes;
    append_integralorfloat_to_ubytesvector<float>(bytes, 10.5);
    REQUIRE(bytes.size() == 4);
    REQUIRE(bytes.at(0) == 0);
    REQUIRE(bytes.at(1) == 0);
    REQUIRE(bytes.at(2) == 40);
    REQUIRE(bytes.at(3) == 65);
  }
  SECTION( "bytestoint16" ) {
    std::array<unsigned char, sizeof(int16_t)> bytes;
    bytes.at(0) = 232;
    bytes.at(1) = 3;
    REQUIRE(ubtyes_to_integeralorfloat<int16_t>(bytes) == 1000);
  }
  SECTION( "bytestoint32" ) {
    std::array<unsigned char, sizeof(int32_t)> bytes;
    bytes.at(0) = 128;
    bytes.at(1) = 181;
    bytes.at(2) = 162;
    bytes.at(3) = 250;
    REQUIRE(ubtyes_to_integeralorfloat<int32_t>(bytes) == -90000000);
  }
  SECTION( "bytestofloat32" ) {
    std::array<unsigned char, sizeof(float)> bytes;
    bytes.at(0) = 0;
    bytes.at(1) = 0;
    bytes.at(2) = 40;
    bytes.at(3) = 65;
    REQUIRE(ubtyes_to_integeralorfloat<float>(bytes) == 10.5);
  }
}
