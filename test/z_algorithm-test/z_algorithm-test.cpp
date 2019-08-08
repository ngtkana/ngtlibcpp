#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <string_algorighms/z_algorithm.hpp>

TEST_CASE("Failure Table Construction Test from snuke's blog.", "[Z Algorithm]") {
  REQUIRE(
    make_z_array("aaabaaaab") ==
    std::vector<int>{9, 2, 1, 0, 3, 4, 2, 1, 0}
  );
}

// https://www.youtube.com/watch?v=CpZh4eF8QBw
TEST_CASE("Failure Table Construction Test from Tushar Roy's movie.", "[Z Algorithm]") {
  REQUIRE(
    make_z_array("aabxaayaab")
    == std::vector<int>{10, 1, 0, 0, 2, 1, 0, 3, 1, 0}
  );
  REQUIRE(
    make_z_array("abc$xabcabzabc")
    == std::vector<int>{14, 0, 0, 0, 0, 3, 0, 0, 2, 0, 0, 3, 0, 0}
  );
  REQUIRE(
    make_z_array("aabxaabxcaabxaabxay")
    == std::vector<int>{19, 1, 0, 0, 4, 1, 0, 0, 0, 8, 1, 0, 0, 5, 1, 0, 0, 1, 0}
  );
}
