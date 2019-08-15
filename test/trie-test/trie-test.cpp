#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <string_algorighms/trie.hpp>
#include "../utility.hpp"

TEST_CASE("Trie Tests", "[Trie]")
{
  auto tri = make_trie<26>(encode_lower_case);
  tri.insert("a");
  tri.insert("to");
  tri.insert("tea");
  tri.insert("ted");
  tri.insert("ten");
  tri.insert("i");
  tri.insert("i");
  tri.insert("in");
  tri.insert("inn");
  tri.insert("to");
  REQUIRE(tri.find("a"  ) == std::vector<int>{0});
  REQUIRE(tri.find("to" ) == std::vector<int>{1, 9});
  REQUIRE(tri.find("ted") == std::vector<int>{3});
  REQUIRE(tri.find("tex") == std::vector<int>{});
  REQUIRE(tri.find("i"  ) == std::vector<int>{5, 6});
}