#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <string_algorighms/suffix_array.hpp>
#include "../utility.hpp"

TEST_CASE("Suffix Array Construction Test" "[Suffix Array]")
{
  SECTION("abracadabra")
  {
    auto suf = suffix_array("abracadabra$");
    suf.build_suffix_array();
    suf.build_lcp_array();
    REQUIRE(suf.get_suffix_array() == std::vector<int>{11, 10, 7, 0, 3, 5, 8, 1, 4, 6, 9, 2});
    REQUIRE(suf.get_lcp_array()    == std::vector<int>{ 0,  1, 4, 1, 1, 0, 3, 0, 0, 0, 2, 0});
  }
  SECTION("banana")
  {
    auto suf = suffix_array("banana$");
    suf.build_suffix_array();
    suf.build_lcp_array();
    REQUIRE(suf.get_suffix_array() == std::vector<int>{6, 5, 3, 1, 0, 4, 2});
    REQUIRE(suf.get_lcp_array()    == std::vector<int>{0, 1, 3, 0, 0, 2, 0});
  }
  SECTION("nagatakana")
  {
    auto suf = suffix_array("nagatakana$");
    suf.build_suffix_array();
    suf.build_lcp_array();
    REQUIRE(suf.get_suffix_array() == std::vector<int>{10, 9, 1, 5, 7, 3, 2, 6, 8, 0, 4});
    REQUIRE(suf.get_lcp_array()    == std::vector<int>{ 0, 1, 1, 1, 1, 0, 0, 0, 2, 0, 0});
  }
  SECTION("acabcabaabaabca")
  {
    auto suf = suffix_array("acabcabaabaabca$");
    suf.build_suffix_array();
    suf.build_lcp_array();
    REQUIRE(suf.get_suffix_array() == std::vector<int>{15, 14, 7, 10, 5, 8, 11, 2, 0, 6, 9, 12, 3, 13, 4, 1});
    REQUIRE(suf.get_lcp_array()    == std::vector<int>{ 0, 1, 3, 1, 5, 2, 4, 1, 0, 4, 1, 3,  0, 2,  3, 0 });
  }
}
