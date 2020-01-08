#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <kmp_algorithm.hpp>

TEST_CASE("Failure Table Construction Test from Wikipedia.", "[KMP Algorithm]") {
  REQUIRE(
    make_failure_table("ABCDABD") ==
    std::vector<int>{-1, 0, 0, 0, -1, 0, 2, 0}
  );
  REQUIRE(
    make_failure_table("ABACABABC") ==
    std::vector<int>{-1, 0, -1, 1, -1, 0, -1, 3, 2, 0}
  );
  REQUIRE(
    make_failure_table("ABACABABA") ==
    std::vector<int>{-1, 0, -1, 1, -1, 0, -1, 3, -1, 3}
  );
  REQUIRE(
    make_failure_table("PARTICIPATE$IN$PARACHUTE") ==
    std::vector<int>{-1, 0, 0, 0, 0, 0, 0, -1, 0, 2, 0, 0, 0, 0, 0, -1, 0, 0, 3, 0, 0, 0, 0, 0, 0}
  );
}
