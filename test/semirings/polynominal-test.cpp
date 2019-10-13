#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <semirings/polynominal.hpp>
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

TEMPLATE_TEST_CASE( "polynominal", "[polynominal]", int, long long ) {
  auto inf = std::numeric_limits< TestType >::max();

  SECTION( "integral ring" ) {
    auto const poly = make_polynominal(
      [](auto x, auto y){ return x * y; },
      [](auto x, auto y){ return x + y; },
      TestType{0}
    );
    auto const deg_max = 20;
    auto const coeff_max = std::sqrt(inf) / deg_max;
    loop(24) {
      auto const k = rand(1, deg_max), l = rand(1, deg_max);
      auto const m = std::max(k, l), n = k + l - 1;
      std::vector< TestType > a(k), b(l);
      for (auto & x : a) x = rand(-coeff_max, coeff_max);
      for (auto & y : b) y = rand(-coeff_max, coeff_max);
      auto const c = poly.add(a, b);
      auto const d = poly.mul(a, b);

      // add test
      auto c_tester = std::vector< TestType >(m, 0);
      rep(i, 0, m) {
        if (i < k) c_tester.at(i) += a.at(i);
        if (i < l) c_tester.at(i) += b.at(i);
      }
      REQUIRE(c == c_tester);

      // mul test
      auto d_tester = std::vector< TestType >(n, 0);
      rep(i, 0, k) rep(j, 0, l) {
        d_tester.at(i + j) += a.at(i) * b.at(j);
      }
      REQUIRE(d == d_tester);
    }
  }

  SECTION( "min-semiring, max-semiring" ) {
    auto const min_poly = make_polynominal(
      [](auto x, auto y){ return x + y; },
      [](auto x, auto y){ return std::min(x, y); },
      inf
    );
    auto const max_poly = make_polynominal(
      [](auto x, auto y){ return x + y; },
      [](auto x, auto y){ return std::max(x, y); },
      -inf
    );
    auto const deg_max = 20;
    auto const coeff_max = inf / 2;
    loop(24) {
      auto const k = rand(1, deg_max), l = rand(1, deg_max);
      auto const m = std::max(k, l), n = k + l - 1;
      std::vector< TestType > a(k), b(l);
      for (auto & x : a) x = rand(-coeff_max, coeff_max);
      for (auto & y : b) y = rand(-coeff_max, coeff_max);
      auto const min_add_result = min_poly.add(a, b);
      auto const min_mul_result = min_poly.mul(a, b);
      auto const max_add_result = max_poly.add(a, b);
      auto const max_mul_result = max_poly.mul(a, b);

      // add test
      std::vector< TestType > min_add_tester(m, inf);
      std::vector< TestType > max_add_tester(m, -inf);
      rep(i, 0, m) {
        if (i < k) {
          cmn(min_add_tester.at(i), a.at(i));
          cmx(max_add_tester.at(i), a.at(i));
        }
        if (i < l) {
          cmn(min_add_tester.at(i), b.at(i));
          cmx(max_add_tester.at(i), b.at(i));
        }
      }
      REQUIRE(min_add_result == min_add_tester);
      REQUIRE(max_add_result == max_add_tester);

      // mul test
      std::vector< TestType > min_mul_tester(n, inf);
      std::vector< TestType > max_mul_tester(n, -inf);
      rep(i, 0, k) rep(j, 0, l) {
        cmn(min_mul_tester.at(i + j), a.at(i) + b.at(j));
        cmx(max_mul_tester.at(i + j), a.at(i) + b.at(j));
      }
      REQUIRE(min_mul_result == min_mul_tester);
      REQUIRE(max_mul_result == max_mul_tester);
    }
  }

  SECTION( "gcd semiring, lcm semiring" ) {
    auto const gcd_poly = make_polynominal(
      [](auto x, auto y){ return x * y; },
      [](auto x, auto y){ return std::__gcd(x, y); },
      TestType{0}
    );
    auto const lcm_poly = make_polynominal(
      [](auto x, auto y){ return x * y; },
      [](auto x, auto y){
        auto g = std::__gcd(x, y);
        return g == 0 ? std::max(x, y) : x / g * y;
      },
      TestType{1}
    );
    auto const deg_max = 4;
    auto const coeff_max = 24;
    loop(24) {
      auto const k = rand(1, deg_max), l = rand(1, deg_max);
      auto const m = std::max(k, l), n = k + l - 1;
      std::vector< TestType > a(k), b(l);
      for (auto & x : a) x = rand(0, coeff_max);
      for (auto & y : b) y = rand(0, coeff_max);
      auto const gcd_add_result = gcd_poly.add(a, b);
      auto const gcd_mul_result = gcd_poly.mul(a, b);
      auto const lcm_add_result = lcm_poly.add(a, b);
      auto const lcm_mul_result = lcm_poly.mul(a, b);
      debug(a, b, gcd_add_result, lcm_add_result);

      // lambdas
      auto gcd_eq = [](auto& x, auto y){ x = std::__gcd(x, y); };
      auto lcm_eq = [](auto& x, auto y) {
        auto const g = std::__gcd(x, y);
        x = g == 0 ? std::max(x, y) : x / g * y;
      };

      // add test
      std::vector< TestType > gcd_add_tester(m, 0);
      std::vector< TestType > lcm_add_tester(m, 1);
      rep(i, 0, m) {
        if (i < k) {
          gcd_eq(gcd_add_tester.at(i), a.at(i));
          lcm_eq(lcm_add_tester.at(i), a.at(i));
        }
        if (i < l) {
          gcd_eq(gcd_add_tester.at(i), b.at(i));
          lcm_eq(lcm_add_tester.at(i), b.at(i));
        }
      }
      REQUIRE(gcd_add_result == gcd_add_tester);
      REQUIRE(lcm_add_result == lcm_add_tester);

      // mul test
      std::vector< TestType > gcd_mul_tester(n, 0);
      std::vector< TestType > lcm_mul_tester(n, 1);
      rep(i, 0, k) rep(j, 0, l) {
        gcd_eq(gcd_mul_tester.at(i + j), a.at(i) * b.at(j));
        lcm_eq(lcm_mul_tester.at(i + j), a.at(i) * b.at(j));
      }
      REQUIRE(gcd_mul_result == gcd_mul_tester);
      REQUIRE(lcm_mul_result == lcm_mul_tester);
    }
  }
}
