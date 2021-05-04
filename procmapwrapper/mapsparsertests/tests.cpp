#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "utility.h"

TEST_CASE( "splitstringintotokens_byspace", "utility"){
  SECTION( "heapline" ) {
    auto vals = utility::splitstringintotokens_byspace(
      "562d31f7b000-562d32123000 rw-p 00000000 00:00 0          [heap]"
    );
    REQUIRE(vals.size() == 6);
    REQUIRE(vals.at(0) == "562d31f7b000-562d32123000");
    REQUIRE(vals.at(1) == "rw-p");
    REQUIRE(vals.at(2) == "00000000");
    REQUIRE(vals.at(3) == "00:00");
    REQUIRE(vals.at(4) == "0");
    REQUIRE(vals.at(5) == "[heap]");
  }
  SECTION( "codeithink" ) {
    auto vals = utility::splitstringintotokens_byspace(
      "562d310db000-562d3110a000 r--p 00000000 08:01 6294567          /usr/bin/bash"
    );
    REQUIRE(vals.size() == 6);
    REQUIRE(vals.at(0) == "562d310db000-562d3110a000");
    REQUIRE(vals.at(1) == "r--p");
    REQUIRE(vals.at(2) == "00000000");
    REQUIRE(vals.at(3) == "08:01");
    REQUIRE(vals.at(4) == "6294567");
    REQUIRE(vals.at(5) == "/usr/bin/bash");
  }
  SECTION( "anonline" ) {
    auto vals = utility::splitstringintotokens_byspace(
      "562d31233000-562d3123e000 rw-p 00000000 00:00 0 "
    );
    REQUIRE(vals.size() == 5);
    REQUIRE(vals.at(0) == "562d31233000-562d3123e000");
    REQUIRE(vals.at(1) == "rw-p");
    REQUIRE(vals.at(2) == "00000000");
    REQUIRE(vals.at(3) == "00:00");
    REQUIRE(vals.at(4) == "0");
  }
}

TEST_CASE( "transform_delimlongstr", "utility" ) {
  SECTION( "typicaladdressrange" ) {
    auto vals = utility::transform_delimlongstr("562d310db000-562d3110a000", '-');
    REQUIRE(vals.size() == 2);
    REQUIRE(vals.at(0) == 94752096497664);
    REQUIRE(vals.at(1) == 94752096690176);
  }
  SECTION( "typicaladdressrange_extraspaces" ) {
    auto vals = utility::transform_delimlongstr(" 562d310db000 - 562d3110a000 ", '-');
    REQUIRE(vals.size() == 2);
    REQUIRE(vals.at(0) == 94752096497664);
    REQUIRE(vals.at(1) == 94752096690176);
  }
  SECTION( "unexpected_emptystring" ) {
    auto vals = utility::transform_delimlongstr("", '-');
    REQUIRE(vals.size() == 0);
  }
  SECTION( "unexpected_secondaddresscutoff" ) {
    auto vals = utility::transform_delimlongstr("562d310db000-", '-');
    REQUIRE(vals.size() == 1);
    REQUIRE(vals.at(0) == 94752096497664);
  }
  SECTION( "unexpected_onlyoneaddress" ) {
    auto vals = utility::transform_delimlongstr("562d310db000", '-');
    REQUIRE(vals.size() == 1);
    REQUIRE(vals.at(0) == 94752096497664);
  }
  SECTION( "unexpected_hyphenonly" ) {
    auto vals = utility::transform_delimlongstr("-", '-');
    REQUIRE(vals.size() == 0);
  }
}
