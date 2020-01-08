#include <catch2/catch.hpp>
#include <bat.hpp>
#include <bits/stdc++.h>

TEST_CASE( "Small" ) {
  REQUIRE(bat(0, 0) == 0);
  REQUIRE(bat(0, 1) == 0);
  REQUIRE(bat(0, 2) == 0);

  REQUIRE(bat(1, 0) == 1);
  REQUIRE(bat(1, 1) == 0);
  REQUIRE(bat(1, 2) == 0);

  REQUIRE(bat(2, 0) == 0);
  REQUIRE(bat(2, 1) == 1);
  REQUIRE(bat(2, 2) == 0);

  REQUIRE(bat(3, 0) == 1);
  REQUIRE(bat(3, 1) == 1);
  REQUIRE(bat(3, 2) == 0);

  REQUIRE(bat(4, 0) == 0);
  REQUIRE(bat(4, 1) == 0);
  REQUIRE(bat(4, 2) == 1);
}

TEST_CASE( "large int" ) {
  int max = std::numeric_limits< int >::max();

  REQUIRE(bat(max, 00) == 1);
  REQUIRE(bat(max, 01) == 1);
  REQUIRE(bat(max, 30) == 1);
  REQUIRE(bat(max, 31) == 0);

  REQUIRE(bat(max-1, 00) == 0);
  REQUIRE(bat(max-1, 01) == 1);
  REQUIRE(bat(max-1, 30) == 1);
  REQUIRE(bat(max-1, 31) == 0);

  REQUIRE(bat(max-2, 00) == 1);
  REQUIRE(bat(max-2, 01) == 0);
  REQUIRE(bat(max-2, 30) == 1);
  REQUIRE(bat(max-2, 31) == 0);

  int min = std::numeric_limits< int >::min();
  REQUIRE(bat(min, 00) == 0);
  REQUIRE(bat(min, 01) == 0);
  REQUIRE(bat(min, 30) == 0);
  REQUIRE(bat(min, 31) == 1);

  REQUIRE(bat(min+1, 00) == 1);
  REQUIRE(bat(min+1, 01) == 0);
  REQUIRE(bat(min+1, 30) == 0);
  REQUIRE(bat(min+1, 31) == 1);

  REQUIRE(bat(min+2, 00) == 0);
  REQUIRE(bat(min+2, 01) == 1);
  REQUIRE(bat(min+2, 30) == 0);
  REQUIRE(bat(min+2, 31) == 1);
}

TEST_CASE( "large long long" ) {
  long long max = std::numeric_limits< long long >::max();

  REQUIRE(bat(max, 00) == 1);
  REQUIRE(bat(max, 01) == 1);
  REQUIRE(bat(max, 62) == 1);
  REQUIRE(bat(max, 63) == 0);

  REQUIRE(bat(max-1, 00) == 0);
  REQUIRE(bat(max-1, 01) == 1);
  REQUIRE(bat(max-1, 62) == 1);
  REQUIRE(bat(max-1, 63) == 0);

  REQUIRE(bat(max-2, 00) == 1);
  REQUIRE(bat(max-2, 01) == 0);
  REQUIRE(bat(max-2, 62) == 1);
  REQUIRE(bat(max-2, 63) == 0);

  long long min = std::numeric_limits< long long >::min();
  REQUIRE(bat(min, 00) == 0);
  REQUIRE(bat(min, 01) == 0);
  REQUIRE(bat(min, 62) == 0);
  REQUIRE(bat(min, 63) == 1);

  REQUIRE(bat(min+1, 00) == 1);
  REQUIRE(bat(min+1, 01) == 0);
  REQUIRE(bat(min+1, 62) == 0);
  REQUIRE(bat(min+1, 63) == 1);

  REQUIRE(bat(min+2, 00) == 0);
  REQUIRE(bat(min+2, 01) == 1);
  REQUIRE(bat(min+2, 62) == 0);
  REQUIRE(bat(min+2, 63) == 1);
}

