#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <algorithm/max_rangesum.hpp>

#define rep(i, begin, end) for(int i = int(begin); i < int(end); i++)
#define loop(h) for (int ngtkana_is_genius = 0; ngtkana_is_genius < int(h); ngtkana_is_genius++)
#define all(v) v.begin(), v.end()
#define rand(l, r) std::uniform_int_distribution<int>(l, r)(mt)
auto cmn = [](auto& a, auto b){if (a > b) {a = b; return true;} return false;};
auto cmx = [](auto& a, auto b){if (a < b) {a = b; return true;} return false;};

std::mt19937_64 mt(std::random_device{}());
auto nmax = 20;
template < class Value >
auto gen() {
  return std::uniform_int_distribution< Value >(
    0,
    10
  )(mt);
}

TEMPLATE_TEST_CASE( "max_rangesum", "[max_rangesum]", int, long long ) {
  loop(24) {
    auto n = rand(1, nmax);
    std::vector< TestType > a(n);
    for (auto & x : a) x = gen< TestType >();
    TestType expected = a.front();
    rep(l, 0, n) rep(r, l+1, n+1) {
      TestType now = 0;
      rep(i, l, r)
        { now += a.at(i); }
      cmx(expected, now);
    }
    REQUIRE(max_rangesum(a) == expected);
  }
}
