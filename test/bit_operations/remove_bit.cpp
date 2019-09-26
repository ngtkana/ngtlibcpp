#include <catch2/catch.hpp>
#include <bit_operations/remove_bit.hpp>
#include <bits/stdc++.h>
#define loop(n) for (int ngtkana_is_genius = 0; ngtkana_is_genius < int(n); ngtkana_is_genius++)
#define rep(i, begin, end) for(int i = int(begin); i < int(end); i++)
#define all(v) v.begin(), v.end()
#define rand(l, r) std::uniform_int_distribution<>(l, r)(mt)
#define lint long long
void debug_impl() { std::cerr << std::endl; }
template <typename Head, typename... Tail>
void debug_impl(Head head, Tail... tail){
  std::cerr << " " << head;
  debug_impl(tail...);
}
#ifndef STOPIT
#define debug(...)\
  std::cerr << std::boolalpha << "[" << #__VA_ARGS__ << "]:";\
  debug_impl(__VA_ARGS__);\
  std::cerr << std::noboolalpha;
#else
#define debug 0;
#endif

template < class > constexpr auto digit = -1;
template <> constexpr auto digit< int       > = 30;
template <> constexpr auto digit< long long > = 60;

TEMPLATE_TEST_CASE( "remove_bit", "[remove_bit]", int, long long ) {
  SECTION( "small cases" ) {
    REQUIRE(remove_bit(TestType(0), 0) == TestType(0));
    REQUIRE(remove_bit(TestType(0), 1) == TestType(0));

    REQUIRE(remove_bit(TestType(1), 0) == TestType(0));
    REQUIRE(remove_bit(TestType(1), 1) == TestType(1));
    REQUIRE(remove_bit(TestType(1), 2) == TestType(1));

    REQUIRE(remove_bit(TestType(2), 0) == TestType(1));
    REQUIRE(remove_bit(TestType(2), 1) == TestType(0));
    REQUIRE(remove_bit(TestType(2), 2) == TestType(2));
  }
  SECTION( "random cases" ) {
    loop(60) {
      auto mt = std::mt19937(std::random_device{}());
      auto n = digit< TestType > - 2;
      std::vector< TestType > a(n);
      for (auto & x : a) x = rand(0, 1);

      TestType x = 0;
      rep(i, 0, n)
        { x += a.at(i) << i; }

      auto j   = rand(0, n - 1);
      a.erase(a.begin() + j);
      TestType y = 0;
      rep(i, 0, n - 1)
        { y += a.at(i) << i; }
      REQUIRE(remove_bit(x, j) == y);
    }
  }
}
