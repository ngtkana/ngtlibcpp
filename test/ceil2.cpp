#include <catch2/catch.hpp>
#include <ceil2.hpp>
#include <bits/stdc++.h>

TEST_CASE( "small" ) {
  REQUIRE(ceil2(0) == 1);
  REQUIRE(ceil2(1) == 1);
  REQUIRE(ceil2(2) == 2);
  REQUIRE(ceil2(3) == 4);
  REQUIRE(ceil2(4) == 4);
  REQUIRE(ceil2(5) == 8);
  REQUIRE(ceil2(6) == 8);
  REQUIRE(ceil2(7) == 8);
  REQUIRE(ceil2(8) == 8);
  REQUIRE(ceil2(9) == 16);
}

TEST_CASE( "large int" ) {
  int large_power = std::numeric_limits< int >::max() / 2 + 1;
  int overflowed = std::numeric_limits< int >::min();
  SECTION( "normal" ) {
    REQUIRE(large_power * 2 == overflowed);
    REQUIRE(ceil2(large_power-2) == large_power);
    REQUIRE(ceil2(large_power-1) == large_power);
    REQUIRE(ceil2(large_power)   == large_power);
  }
  SECTION( "overflow" ) {
    REQUIRE(ceil2(large_power+1) == overflowed);
    REQUIRE(ceil2(large_power+2) == overflowed);
  }
  SECTION( "beyond overflow" ) {
    REQUIRE(ceil2(overflowed-1) == overflowed);
    REQUIRE(ceil2(overflowed) == overflowed);
    REQUIRE(ceil2(overflowed+1) == 1);
    REQUIRE(ceil2(overflowed+2) == 1);
    REQUIRE(ceil2(overflowed+3) == 1);
    REQUIRE(ceil2(overflowed+3) == 1);
  }
}

TEST_CASE( "large long long" ) {
  long long large_power = std::numeric_limits< long long >::max() / 2 + 1;
  long long overflowed = std::numeric_limits< long long >::min();
  SECTION( "normal" ) {
    REQUIRE(large_power * 2 == overflowed);
    REQUIRE(ceil2(large_power-2) == large_power);
    REQUIRE(ceil2(large_power-1) == large_power);
    REQUIRE(ceil2(large_power)   == large_power);
  }
}