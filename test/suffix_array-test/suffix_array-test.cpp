#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <string_algorighms/suffix_array.hpp>
#include "../utility.hpp"

TEST_CASE("Suffix Array Construction Test", "[Suffix Array]")
{
  auto suf = suffix_array("abracadabra$");
  REQUIRE(suf == std::vector<int>{11, 10, 7, 0, 3, 5, 8, 1, 4, 6, 9, 2});
}
