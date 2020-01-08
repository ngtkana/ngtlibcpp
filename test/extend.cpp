#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <extend.hpp>

#define rep(i, begin, end) for(int i = int(begin); i < int(end); i++)
#define loop(h) for (int ngtkana_is_genius = 0; ngtkana_is_genius < int(h); ngtkana_is_genius++)
#define all(v) v.begin(), v.end()
#define rand(l, r) std::uniform_int_distribution<int>(l, r)(mt)
auto cmn = [](auto& a, auto b){if (a > b) {a = b; return true;} return false;};
auto cmx = [](auto& a, auto b){if (a < b) {a = b; return true;} return false;};

std::mt19937_64 mt(std::random_device{}());

TEST_CASE( "Random" ) {
  auto size_max = 20;
  loop(24) {
    auto n = rand(1, size_max / 2);
    auto k = rand(1, size_max);
    std::vector< int > a(n);
    auto b = extend(a, k);
    REQUIRE((int)b.size() == k);
    loop(n) {
      auto i = rand(0, k - 1);
      REQUIRE(b.at(i) == a.at(i % n));
    }
  }
}
