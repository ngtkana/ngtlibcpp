#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <max_rangesum.hpp>

#define rep(i, begin, end) for(int i = int(begin); i < int(end); i++)
#define loop(h) for (int ngtkana_is_genius = 0; ngtkana_is_genius < int(h); ngtkana_is_genius++)
#define all(v) v.begin(), v.end()
#define rand(l, r) std::uniform_int_distribution<int>(l, r)(mt)
auto cmn = [](auto& a, auto b){if (a > b) {a = b; return true;} return false;};
auto cmx = [](auto& a, auto b){if (a < b) {a = b; return true;} return false;};

std::mt19937_64 mt(std::random_device{}());

TEST_CASE( "Tutorial" ) {
  std::vector< int > a = { 4, -6, 0, 3, 2, -3, 1, 7 };
  REQUIRE(max_rangesum(a) == 3+2-3+1+7);
}
TEST_CASE( "Random" ) {
  int size_max = 20;
  loop(24) {
    auto n = rand(1, size_max);
    std::vector< int > a(n);
    auto ret = 0;
    rep(l, 0, n) rep(r, l + 1, n) {
      auto now = 0;
      rep(i, l, r)
        { now += a.at(i); }
      cmx(ret, now);
    }
    REQUIRE(max_rangesum(a) == ret);
  }
}
