#include <catch2/catch.hpp>
#include <bit_operations/insert_bit.hpp>
#include <bits/stdc++.h>
#define loop(n) for (int ngtkana_is_genius = 0; ngtkana_is_genius < int(n); ngtkana_is_genius++)
#define rep(i, begin, end) for(int i = int(begin); i < int(end); i++)
#define all(v) v.begin(), v.end()
#define rand(l, r) std::uniform_int_distribution<>(l, r)(mt)
#define lint long long
auto cmn = [](auto& a, auto b){if (a > b) {a = b; return true;} return false;};
auto cmx = [](auto& a, auto b){if (a < b) {a = b; return true;} return false;};
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

TEMPLATE_TEST_CASE( "insert_bit", "[insert_bit]", int, long long ) {
  SECTION( "small cases" ) {
    REQUIRE(insert_bit(TestType(0), 0, false) == TestType(0));
    REQUIRE(insert_bit(TestType(0), 0, true ) == TestType(1));
    REQUIRE(insert_bit(TestType(0), 1, false) == TestType(0));
    REQUIRE(insert_bit(TestType(0), 1, true ) == TestType(2));

    REQUIRE(insert_bit(TestType(1), 0, false) == TestType(2));
    REQUIRE(insert_bit(TestType(1), 0, true ) == TestType(3));
    REQUIRE(insert_bit(TestType(1), 1, false) == TestType(1));
    REQUIRE(insert_bit(TestType(1), 1, true ) == TestType(3));
    REQUIRE(insert_bit(TestType(1), 2, false) == TestType(1));
    REQUIRE(insert_bit(TestType(1), 2, true ) == TestType(5));

    REQUIRE(insert_bit(TestType(2), 0, false) == TestType(4));
    REQUIRE(insert_bit(TestType(2), 0, true ) == TestType(5));
    REQUIRE(insert_bit(TestType(2), 1, false) == TestType(4));
    REQUIRE(insert_bit(TestType(2), 1, true ) == TestType(6));
    REQUIRE(insert_bit(TestType(2), 2, false) == TestType(2));
    REQUIRE(insert_bit(TestType(2), 2, true ) == TestType(6));
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
      auto bit = rand(0, 1);
      a.insert(a.begin() + j, bit);
      TestType y = 0;
      rep(i, 0, n + 1)
        { y += a.at(i) << i; }
      REQUIRE(insert_bit(x, j, bit) == y);
    }
  }
}
