#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <coenumerate.hpp>
#include <enumerate.hpp>
#define rep(i, begin, end) for(int i = int(begin); i < int(end); i++)
#define loop(h) for (int ngtkana_is_genius = 0; ngtkana_is_genius < int(h); ngtkana_is_genius++)
#define all(v) v.begin(), v.end()
#define rand(l, r) std::uniform_int_distribution<int>(l, r)(mt)
auto cmn = [](auto& a, auto b){if (a > b) {a = b; return true;} return false;};
auto cmx = [](auto& a, auto b){if (a < b) {a = b; return true;} return false;};
std::mt19937_64 mt(std::random_device{}());

TEST_CASE( "enuerate, coenumerate", "[enumerate, coenumerate]" ) {
  auto nmax  = 20;
  auto max   = 1'000'000'000;

  loop(24) {
    auto n = rand(1, nmax);
    std::vector< int > a(n);
    for (auto & x : a) x = rand(1, max);

    SECTION( "coenumerate" ) {
      auto const coe = coenumerate(a);
      auto i = rand(0, n - 1);
      REQUIRE(coe.at(i).first  == a.at(i));
      REQUIRE(coe.at(i).second == i);
    }

    SECTION( "enumerate" ) {
      auto const enm = enumerate(a);
      auto i = rand(0, n - 1);
      REQUIRE(enm.at(i).first  == i);
      REQUIRE(enm.at(i).second == a.at(i));
    }
  }
}
