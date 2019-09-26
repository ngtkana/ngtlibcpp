#include <catch2/catch.hpp>
#include <bit_operations/ceil2.hpp>
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

TEMPLATE_TEST_CASE( "ceil2", "[ceil2]", int, long long ) {
  SECTION( "small cases" ) {
    REQUIRE(ceil2(TestType(0)) == 1);
    REQUIRE(ceil2(TestType(1)) == 1);
    REQUIRE(ceil2(TestType(2)) == 2);
    REQUIRE(ceil2(TestType(3)) == 4);
    REQUIRE(ceil2(TestType(4)) == 4);
    REQUIRE(ceil2(TestType(5)) == 8);
  }
  SECTION( "random cases" ) {
    loop(60) {
      auto mt = std::mt19937(std::random_device{}());
      auto n = rand(3, digit< TestType > - 1);
      std::vector< TestType > a(n);
      for (auto & x : a) x = rand(0, 1);
      a.emplace_back(1);
      n++;
      TestType val = 0;
      rep(i, 0, n)
        { val += a.at(i) << i; }
      REQUIRE(val <= ceil2(val));
      REQUIRE(ceil2(val) < val * 2);
    }
  }
  SECTION( "boundary cases ") {
    loop(60) {
      auto mt = std::mt19937(std::random_device{}());
      auto n = rand(3, digit< TestType > - 1);
      for (auto dx : {-2, -1, 0, 1, 2}) {
        auto val = (TestType(1) << n) + dx;
        REQUIRE(val <= ceil2(val));
        REQUIRE(ceil2(val) < val * 2);
      }
    }
  }
}
