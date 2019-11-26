#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <algorithm/max_rangesum.hpp>
#include <algorithm/extend.hpp>
#include <algorithm/keys.hpp>
#include <algorithm/values.hpp>

#define rep(i, begin, end) for(int i = int(begin); i < int(end); i++)
#define loop(h) for (int ngtkana_is_genius = 0; ngtkana_is_genius < int(h); ngtkana_is_genius++)
#define all(v) v.begin(), v.end()
#define rand(l, r) std::uniform_int_distribution<int>(l, r)(mt)
auto cmn = [](auto& a, auto b){if (a > b) {a = b; return true;} return false;};
auto cmx = [](auto& a, auto b){if (a < b) {a = b; return true;} return false;};

std::mt19937_64 mt(std::random_device{}());

TEST_CASE( "Algorithms on Sequences", "[enumerate, coenumerate, zip]" ) {
  auto nmax    = 20;
  SECTION( "max_rangesum" ) {
    loop(24) {
      auto n = rand(1, nmax);
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
  SECTION( "extend" ) {
    loop(24) {
      auto n = rand(1, nmax / 2);
      auto k = rand(1, nmax);
      std::vector< int > a(n);
      auto b = extend(a, k);
      REQUIRE((int)b.size() == k);
      loop(n) {
        auto i = rand(0, k - 1);
        REQUIRE(b.at(i) == a.at(i % n));
      }
    }
  }
}
