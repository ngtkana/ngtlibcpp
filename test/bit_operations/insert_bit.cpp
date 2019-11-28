#include <catch2/catch.hpp>
#include <bit_operations/insert_bit.hpp>
#include <bits/stdc++.h>

TEST_CASE( "small" ) {
  REQUIRE(insert_bit(0, 0, false) == 0);
  REQUIRE(insert_bit(0, 0, true ) == 1);
  REQUIRE(insert_bit(0, 1, false) == 0);
  REQUIRE(insert_bit(0, 1, true ) == 2);

  REQUIRE(insert_bit(1, 0, false) == 2);
  REQUIRE(insert_bit(1, 0, true ) == 3);
  REQUIRE(insert_bit(1, 1, false) == 1);
  REQUIRE(insert_bit(1, 1, true ) == 3);
  REQUIRE(insert_bit(1, 2, false) == 1);
  REQUIRE(insert_bit(1, 2, true ) == 5);

  REQUIRE(insert_bit(2, 0, false) == 4);
  REQUIRE(insert_bit(2, 0, true ) == 5);
  REQUIRE(insert_bit(2, 1, false) == 4);
  REQUIRE(insert_bit(2, 1, true ) == 6);
  REQUIRE(insert_bit(2, 2, false) == 2);
  REQUIRE(insert_bit(2, 2, true ) == 6);
}
