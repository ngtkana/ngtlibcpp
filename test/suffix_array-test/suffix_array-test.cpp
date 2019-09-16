#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <string_algorighms/suffix_array.hpp>
#include "../utility.hpp"
#define rep(i, begin, end) for(int i = int(begin); i < int(end); i++)
#define loop(n) for (int ngtkana_is_genius = 0; ngtkana_is_genius < int(n); ngtkana_is_genius++)
#define rand(l, r) std::uniform_int_distribution<>(l, r)(mt)

TEST_CASE( "Suffix Array Construction Test" "[Suffix Array]" ) {
  SECTION( "abracadabra" ) {
    auto sa = suffix_array( "abracadabra" );
    sa.build();
    REQUIRE(sa.get_suf() == std::vector<int>{ 10, 7, 0, 3, 5, 8, 1, 4, 6, 9, 2 });
    REQUIRE(sa.get_lcp() == std::vector<int>{  1, 4, 1, 1, 0, 3, 0, 0, 0, 2, 0 });
  }
  SECTION( "banana" ) {
    auto sa = suffix_array( "banana" );
    sa.build();
    REQUIRE(sa.get_suf() == std::vector<int>{ 5, 3, 1, 0, 4, 2 });
    REQUIRE(sa.get_lcp() == std::vector<int>{ 1, 3, 0, 0, 2, 0 });
  }
  SECTION( "nagatakana" ) {
    auto sa = suffix_array( "nagatakana" );
    sa.build();
    REQUIRE(sa.get_suf() == std::vector<int>{ 9, 1, 5, 7, 3, 2, 6, 8, 0, 4 });
    REQUIRE(sa.get_lcp() == std::vector<int>{ 1, 1, 1, 1, 0, 0, 0, 2, 0, 0 });
  }
  SECTION( "Random Test" ) {
    loop(24) {
      std::mt19937 mt(std::random_device{}());
      auto n = rand(1, 40);
      std::string s;
      loop(n) s.push_back('a' + rand(0, 1));
      auto sa = suffix_array(s);
      sa.build();
      auto suf = sa.get_suf();
      auto lcp = sa.get_lcp();

      rep(i, 0, n - 1) {
        auto x = suf.at(i), y = suf.at(i + 1);
        REQUIRE( s.substr(x) < s.substr(y) );
        auto z = 0;
        while (x < n && y < n) {
          if (s.at(x) != s.at(y)) break;
          x++, y++, z++;
        }
        REQUIRE( lcp.at(i) == z );
      }
    }
  }
}
