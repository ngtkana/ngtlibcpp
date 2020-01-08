#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <sliding_minimum.hpp>
#define loop(n) for (int ngtkana_is_genius = 0; ngtkana_is_genius < int(n); ngtkana_is_genius++)
#define rep(i, begin, end) for(int i = int(begin); i < int(end); i++)
#define all(v) v.begin(), v.end()
#define rand(l, r) std::uniform_int_distribution<>(l, r)(mt)
using lint = long long;
auto mt = std::mt19937_64(std::random_device{}());
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

TEMPLATE_TEST_CASE( "sliding_minimum", "[sliding_minimum]", int, long long ) {
  auto inf = std::numeric_limits< TestType >::max();
  loop(24) {
    auto n = rand(1, 40);
    std::vector< TestType >a(n);
    for (auto & x : a) x = rand(-inf - 1, inf);
    auto k = rand(1, n);

    auto min = make_sliding_minimum(a, [](auto x, auto y){ return x < y; });
    auto max = make_sliding_minimum(a, [](auto x, auto y){ return x > y; });
    auto l = 0, r = k;
    min.advance_to(l, r);
    max.advance_to(l, r);
    while (true) {
      REQUIRE(min.query() == *std::min_element(a.begin() + l, a.begin() + r));
      REQUIRE(max.query() == *std::max_element(a.begin() + l, a.begin() + r));
      REQUIRE(min.query() == a.at(min.query_index()));
      REQUIRE(max.query() == a.at(max.query_index()));
      if (r == n) break;
      l++, r++, min.slide(), max.slide();
    }
  }
}
