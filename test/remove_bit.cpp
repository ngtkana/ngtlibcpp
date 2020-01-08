#include <catch2/catch.hpp>
#include <remove_bit.hpp>
#include <bits/stdc++.h>

TEST_CASE( "small" ) {
  REQUIRE(remove_bit(0, 0) == 0);
  REQUIRE(remove_bit(0, 1) == 0);

  REQUIRE(remove_bit(1, 0) == 0);
  REQUIRE(remove_bit(1, 1) == 1);
  REQUIRE(remove_bit(1, 2) == 1);

  REQUIRE(remove_bit(2, 0) == 1);
  REQUIRE(remove_bit(2, 1) == 0);
  REQUIRE(remove_bit(2, 2) == 2);
}
