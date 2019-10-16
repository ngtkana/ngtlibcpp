#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <range_queries/segment_tree.hpp>
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



TEMPLATE_TEST_CASE( "segment_tree", "[segment_tree]", int long long ) {
  constexpr auto inf = std::numeric_limits< TestType >::max();
  auto const test_rand = [](auto l, auto r)
    { return std::uniform_int_distribution< TestType >(l, r)(mt); };
  SECTION( "point-add, range-sum") {
    loop(1) {
      auto n = rand(1, 8), q = 2 * n;
      std::vector< TestType > a(n);
      auto max = inf / (n * q);
      for (auto & x : a) x = test_rand(-max, max);
      auto seg = make_segment_tree(
        n,
        [](auto x, auto y){ return x + y; },
        TestType{0}
      );
      rep(i, 0, n)
        { seg.at(i) = a.at(i); }
      seg.build();
      loop(q) {
        if (rand(0, 1)) {
          auto p = rand(0, n - 1);
          auto x = test_rand(-max, max);
          a.at(p) += x;
          seg.at(p) += x;
          seg.build();
        } else {
          auto l = rand(0, n - 1), r = rand(0, n - 1);
          if (r < l) std::swap(l, r);
          r++;
          REQUIRE(
            seg.query(l, r) ==
            std::accumulate(a.begin() + l, a.begin() + r, TestType{0})
          );
        }
        REQUIRE(seg.collect() == a);
      }
    }
  }
}
