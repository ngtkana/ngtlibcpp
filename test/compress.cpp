#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <compress.hpp>
#include <bits/stdc++.h>
#define rep(i, begin, end) for(int i = int(begin); i < int(end); i++)
#define loop(h) for (int ngtkana_is_genius = 0; ngtkana_is_genius < int(h); ngtkana_is_genius++)
#define all(v) v.begin(), v.end()
#define rand(l, r) std::uniform_int_distribution<int>(l, r)(mt)

std::mt19937_64 mt(std::random_device{}());
template < class Value >
auto gen() {
  return std::uniform_int_distribution< Value >(
    std::numeric_limits< Value >::min(),
    std::numeric_limits< Value >::max()
  )(mt);
}

TEMPLATE_TEST_CASE( "compress", "[compress]", int, long long ) {
  auto nmax = 20;
  loop(24) {
    auto n = rand(1, nmax);
    std::vector< TestType > a(n);
    for (auto & x : a) x = gen< TestType >();
    auto ret = compress(a);
    rep(i, 0, n) rep(j, i + 1, n) {
      REQUIRE((a.at(i) < a.at(j)) == (ret.at(i) < ret.at(j)));
      REQUIRE((a.at(i) > a.at(j)) == (ret.at(i) > ret.at(j)));
    }
    std::sort(all(a));
    std::sort(all(ret));
    a.resize(std::unique(all(a)) - a.begin());
    ret.resize(std::unique(all(ret)) - ret.begin());
    REQUIRE(a.size() == ret.size());
    REQUIRE((int)ret.size() - 1 == ret.back());
  }
}
