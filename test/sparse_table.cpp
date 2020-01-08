#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#define loop(n) for (int ngtkana_is_genius = 0; ngtkana_is_genius < int(n); ngtkana_is_genius++)
#define rep(i, begin, end) for(int i = int(begin); i < int(end); i++)
#define all(v) v.begin(), v.end()
#define rand(l, r) std::uniform_int_distribution<>(l, r)(mt)
using lint = long long;
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

template < typename Container, typename Value = typename Container::value_type, std::enable_if_t<!std::is_same< Container, std::string >::value, std::nullptr_t> = nullptr>
std::istream& operator>> (std::istream& is, Container& v)
  { for (auto & x : v) { is >> x; } return is; }

template < typename Container, typename Value = typename Container::value_type, std::enable_if_t<!std::is_same< Container, std::string >::value, std::nullptr_t> = nullptr >
std::ostream& operator<< (std::ostream& os, Container const& v) {
 os << "{";
  for (auto it = v.begin(); it != v.end(); it++)
    {os << (it != v.begin() ? "," : "") << *it;}
  return os << "}";
}
#include <sparse_table.hpp>

auto mt = std::mt19937_64(std::random_device{}());
template < class T >
auto random_interval(T n) {
  auto l = rand(0, n - 1), r = rand(0, n - 1);
  if (r < l) std::swap(l, r);
  r++;
  return std::make_pair(l, r);
}

TEMPLATE_TEST_CASE( "Sparse Table", "[sparse_table]", int, long long ) {
  constexpr auto inf = std::numeric_limits< TestType >::max();
  SECTION( "min, max, gcd" ) {
    loop(24) {
      auto n = rand(1, 40);
      auto a = std::vector< TestType >(n);
      for (auto & x : a)
        { x = std::uniform_int_distribution< TestType >(0,inf)(mt); }

      auto min_table = make_sparse_table(a, [](auto x, auto y){ return std::min(x, y); });
      auto max_table = make_sparse_table(a, [](auto x, auto y){ return std::max(x, y); });
      auto gcd_table = make_sparse_table(a, [](auto x, auto y){ return std::__gcd(x, y); });

      loop(24) {
        int l, r; std::tie(l, r) = random_interval(n);
        REQUIRE(min_table.query(l, r) == *std::min_element(a.begin() + l, a.begin() + r));
        REQUIRE(max_table.query(l, r) == *std::max_element(a.begin() + l, a.begin() + r));
        REQUIRE(gcd_table.query(l, r) == std::accumulate(a.begin() + l, a.begin() + r, TestType{0},
          [](auto x, auto y){ return std::__gcd(x, y); }));
      }
    }
  }

  SECTION( "sum" ) {
    loop(24) {
      auto n = rand(1, 40);
      auto a = std::vector< TestType >(n);
      for (auto & x : a)
        { x = std::uniform_int_distribution< TestType >(0, inf / n)(mt); }

      auto sum_table = make_sparse_table(a, [](auto x, auto y){ return x + y; });

      loop(24) {
        int l, r; std::tie(l, r) = random_interval(n);
        REQUIRE(sum_table.query(l, r) == std::accumulate(a.begin() + l, a.begin() + r, TestType{0}));
      }
    }
  }

  SECTION( "composition of linear functions" ) {
    loop(24) {
      auto n = rand(1, 12);
      auto a = std::vector< std::pair< TestType, TestType > >(n);
      for (auto & pair : a) {
        TestType x, y; std::tie(x, y) = pair;
        x = std::uniform_int_distribution< TestType >(-2, 2)(mt);
        y = std::uniform_int_distribution< TestType >(-10'000, 10'000)(mt);
      }

      auto cmp_fn = [](auto p, auto q){
        TestType a, b, c, d; std::tie(a, b) = p, std::tie(c, d) = q;
        return std::make_pair(a * c, a * d + b);
      };
      auto cmp_table = make_sparse_table(a, cmp_fn);

      loop(24) {
        int l, r; std::tie(l, r) = random_interval(n);
        REQUIRE(cmp_table.query(l, r) == std::accumulate(a.begin() + l, a.begin() + r,
          std::make_pair(TestType{1}, TestType{0}), cmp_fn));
      }
    }
  }

  SECTION( "composition of linear fractional transformations" ) {
    loop(24) {
      auto n = rand(1, 12);
      auto a = std::vector< std::tuple< TestType, TestType, TestType, TestType > >(n);
      for (auto & tuple : a) {
        TestType a, b, c, d; std::tie(a, b, c, d) = tuple;
        a = std::uniform_int_distribution< TestType >(-2, 2)(mt);
        b = std::uniform_int_distribution< TestType >(-2, 2)(mt);
        c = std::uniform_int_distribution< TestType >(-2, 2)(mt);
        d = std::uniform_int_distribution< TestType >(-2, 2)(mt);
      }

      auto cmp_fn = [](auto p, auto q){
        TestType a, b, c, d; std::tie(a, b, c, d) = p;
        TestType e, f, g, h; std::tie(e, f, g, h) = q;
        return std::make_tuple(a * e + b * g, a * f + b * h, c * e + d * g, c * f + d * h);
      };
      auto cmp_table = make_sparse_table(a, cmp_fn);

      loop(24) {
        int l, r; std::tie(l, r) = random_interval(n);
        REQUIRE(cmp_table.query(l, r) == std::accumulate(a.begin() + l, a.begin() + r,
          std::make_tuple(TestType{1}, TestType{0}, TestType{0}, TestType{1}), cmp_fn));
      }
    }
  }
}
