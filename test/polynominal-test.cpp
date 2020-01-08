#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <polynominal.hpp>
#include <mint.hpp>
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

TEMPLATE_TEST_CASE( "integral", "[polynominal]", int, long long ) {
  auto const poly = make_polynominal(
    [](auto x, auto y){ return x + y; },
    [](auto x, auto y){ return x * y; },
    TestType{0},
    [](auto x, auto y){ return x - y; }
  );
  using vec_t = std::vector< TestType >;

  SECTION( "normalize" ) {
    REQUIRE( poly.normalized(vec_t{0, 2, 0, 0}) == vec_t{0, 2} );
    REQUIRE( poly.normalized(vec_t{0, 2, 0, 1}) == vec_t{0, 2, 0, 1} );
    REQUIRE( poly.normalized(vec_t{0, 0, 0, 0}) == vec_t{} );
    REQUIRE( poly.normalized(vec_t{}) == vec_t{} );
  }

  SECTION( "eval" ) {
    REQUIRE( poly.eval(vec_t{1, 10, 100, 1000, 0}, 0) == 1 );
    REQUIRE( poly.eval(vec_t{1, 10, 100, 1000, 0}, 1) == 1111 );
    REQUIRE( poly.eval(vec_t{1, 10, 100, 1000, 0}, 2) == 8421 );
    REQUIRE( poly.eval(vec_t{1, 10, 100, 1000, 0}, 3) == 27931 );
    REQUIRE( poly.eval(vec_t{}, 1) == 0 );
  }

  SECTION( "add" ) {
    REQUIRE( poly.add(vec_t{1, 2}, vec_t{3, 4, 5}) == vec_t{4, 6, 5} );
    REQUIRE( poly.add(vec_t{1, 2}, vec_t{1, -2}) == vec_t{2} );
    REQUIRE( poly.add(vec_t{1, 2}, vec_t{-1, -2}) == vec_t{} );
  }

  SECTION( "mul" ) {
    REQUIRE( poly.mul(vec_t{1, 2}, vec_t{1, 3}) == vec_t{1, 5, 6} );
    REQUIRE( poly.mul(vec_t{1, 2, 0}, vec_t{1, 3, 0}) == vec_t{1, 5, 6} );
    REQUIRE( poly.mul(vec_t{1, 2}, vec_t{1}) == vec_t{1, 2} );
    REQUIRE( poly.mul(vec_t{1, 2}, vec_t{}) == vec_t{});
    REQUIRE( poly.mul(vec_t{}, vec_t{}) == vec_t{} );
  }

  SECTION( "sub" ) {
    REQUIRE( poly.sub(vec_t{1, 2}, vec_t{1, 1}) == vec_t{0, 1} );
    REQUIRE( poly.sub(vec_t{1, 2, 0}, vec_t{1, 1, 0}) == vec_t{0, 1} );
    REQUIRE( poly.sub(vec_t{1, 2}, vec_t{0, 2}) == vec_t{1} );
    REQUIRE( poly.sub(vec_t{1, 2}, vec_t{1, 2}) == vec_t{} );
  }
}

TEST_CASE( "mint", "[polynominal]" ) {
  using mint = modular< std::integral_constant< int, 3 > >;
  auto const poly = make_polynominal(
    [](auto x, auto y){ return x + y; },
    [](auto x, auto y){ return x * y; },
    mint(0),
    [](auto x, auto y){ return x - y; },
    [](auto x, auto y){ return x / y; }
  );
  using vec_t = std::vector< mint >;

  SECTION( "normalize" ) {
    REQUIRE( poly.normalized(vec_t{0, 2, 0, 0}) == vec_t{0, 2} );
    REQUIRE( poly.normalized(vec_t{0, 2, 0, 1}) == vec_t{0, 2, 0, 1} );
    REQUIRE( poly.normalized(vec_t{0, 0, 0, 0}) == vec_t{} );
    REQUIRE( poly.normalized(vec_t{}) == vec_t{} );
  }

  SECTION( "eval" ) {
    REQUIRE( poly.eval(vec_t{1, 10, 100, 1000, 0}, 0) == 1 );
    REQUIRE( poly.eval(vec_t{1, 10, 100, 1000, 0}, 1) == 1 );
    REQUIRE( poly.eval(vec_t{1, 10, 100, 1000, 0}, 2) == 0 );
    REQUIRE( poly.eval(vec_t{1, 10, 100, 1000, 0}, 3) == 1 );
    REQUIRE( poly.eval(vec_t{}, 1) == 0 );
  }

  SECTION( "add" ) {
    REQUIRE( poly.add(vec_t{1, 2}, vec_t{3, 4, 5}) == vec_t{4, 6, 5} );
    REQUIRE( poly.add(vec_t{1, 2}, vec_t{1, -2}) == vec_t{2} );
    REQUIRE( poly.add(vec_t{1, 2}, vec_t{-1, -2}) == vec_t{} );
  }

  SECTION( "mul" ) {
    REQUIRE( poly.mul(vec_t{1, 2}, vec_t{1, 3}) == vec_t{1, 5} ); // 6 == 0
    REQUIRE( poly.mul(vec_t{1, 2, 0}, vec_t{1, 3, 0}) == vec_t{1, 5} );
    REQUIRE( poly.mul(vec_t{1, 2}, vec_t{1}) == vec_t{1, 2} );
    REQUIRE( poly.mul(vec_t{1, 2}, vec_t{}) == vec_t{});
    REQUIRE( poly.mul(vec_t{}, vec_t{}) == vec_t{} );
  }

  SECTION( "sub" ) {
    REQUIRE( poly.sub(vec_t{1, 2}, vec_t{1, 1}) == vec_t{0, 1} );
    REQUIRE( poly.sub(vec_t{1, 2, 0}, vec_t{1, 1, 0}) == vec_t{0, 1} );
    REQUIRE( poly.sub(vec_t{1, 2}, vec_t{0, 2}) == vec_t{1} );
    REQUIRE( poly.sub(vec_t{1, 2}, vec_t{1, 2}) == vec_t{} );
  }

  SECTION( "div" ) {
    REQUIRE( poly.div(vec_t{1, 1, 1}, vec_t{1, 1}) == std::make_pair(vec_t{0, 1}, vec_t{1}));
    REQUIRE( poly.div(vec_t{1, 1}, vec_t{1, 1, 1}) == std::make_pair(vec_t{}, vec_t{1, 1}));
    REQUIRE( poly.div(vec_t{1, 1, 1, 3}, vec_t{1, 1, 3}) == std::make_pair(vec_t{0, 1}, vec_t{1}));
  }
}

template < class Add, class Mul, class Value >
auto distributive(Add const& add, Mul const& mul, Value zero) {
  auto const deg_max = 4;
  auto const value_max = 8;
  auto const iteration = 24;

  using vec_t = std::vector< Value >;
  auto const poly = make_polynominal(add, mul, zero);
  auto const random_poly = [&poly, deg_max, value_max] {
    auto a = vec_t(rand(0, deg_max));
    for (auto & x : a) x = std::uniform_int_distribution< Value >(1, value_max)(mt);
    return poly.normalized(a);
  };

  loop(iteration) {
    auto const a = random_poly();
    auto const b = random_poly();
    auto const c = random_poly();
    REQUIRE(poly.mul(poly.add(a, b), c) == poly.add(poly.mul(a, c), poly.mul(b, c)));
  }
}

#define BINARY_OP(f) [](auto x, auto y){ return f; }
TEMPLATE_TEST_CASE( "distributiveness test", "[polynominal]", int, long long ) {
  distributive( BINARY_OP(x + y), BINARY_OP(x * y), TestType{0} );
  distributive( BINARY_OP(x ^ y), BINARY_OP(x & y), TestType{0} );
  distributive( BINARY_OP(x | y), BINARY_OP(x & y), TestType{0} );
  distributive( BINARY_OP(std::min(x, y)), BINARY_OP(x + y), std::numeric_limits< TestType >::max() );
  distributive( BINARY_OP(std::max(x, y)), BINARY_OP(x + y), std::numeric_limits< TestType >::min() );
  distributive( BINARY_OP(std::min(x, y)), BINARY_OP(std::max(x, y)), std::numeric_limits< TestType >::max() );
  distributive( BINARY_OP(std::max(x, y)), BINARY_OP(std::min(x, y)), std::numeric_limits< TestType >::min() );
  distributive( BINARY_OP(std::__gcd(x, y)), BINARY_OP(x * y), TestType{0} );
}
