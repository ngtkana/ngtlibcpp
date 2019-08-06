#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <datasets_and_queries/union_find_tree.cpp>

TEST_CASE("union find", "[union-find]") {
  auto uft = union_find_tree(3);
  REQUIRE( uft.is_equiv(0, 0));
  REQUIRE(!uft.is_equiv(0, 1));
  uft.unite(0, 1);
  REQUIRE( uft.is_equiv(0, 1));
}
