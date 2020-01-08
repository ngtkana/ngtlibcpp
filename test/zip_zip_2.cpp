#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <zip2.hpp>
#include <zip.hpp>
#define loop(h) for (int ngtkana_is_genius = 0; ngtkana_is_genius < int(h); ngtkana_is_genius++)
#define rand(l, r) std::uniform_int_distribution<>(l, r)(mt)

std::mt19937_64 mt(std::random_device{}());
template < class Value >
auto gen() {
  return std::uniform_int_distribution< Value >(
    std::numeric_limits< Value >::min(),
    std::numeric_limits< Value >::max()
  )(mt);
}

TEMPLATE_TEST_CASE( "zip", "[zip]", int, long long ) {
  constexpr int nmax = 20;
  SECTION( "zip2" ) {
    loop(24) {
      auto n = rand(1, nmax);
      std::vector< TestType > a(n), b(n);
      for (auto & x : a) x = gen< TestType >();
      for (auto & x : b) x = gen< TestType >();
      auto const ret = zip2(a, b);
      auto i = rand(0, n - 1);
      REQUIRE(ret.at(i).first  == a.at(i));
      REQUIRE(ret.at(i).second == b.at(i));
    }
  }
  SECTION( "zip" ) {
    loop(24) {
      auto n = rand(1, nmax);
      std::vector< TestType > a(n), b(n), c(n);
      for (auto & x : a) x = gen< TestType >();
      for (auto & x : b) x = gen< TestType >();
      for (auto & x : c) x = gen< TestType >();
      auto const ret = zip(a, b, c);
      auto i = rand(0, n - 1);
      REQUIRE(std::get< 0 >(ret.at(i)) == a.at(i));
      REQUIRE(std::get< 1 >(ret.at(i)) == b.at(i));
      REQUIRE(std::get< 2 >(ret.at(i)) == c.at(i));
    }
  }
}
