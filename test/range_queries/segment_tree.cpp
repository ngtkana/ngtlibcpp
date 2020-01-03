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

auto const config = [](auto higher_generator, auto merge_id, auto act) {
  auto const n = rand(1, 8);
  auto const q = 2 * n;
  auto const generator = higher_generator(n, q);
  auto vec = std::vector< std::decay_t< decltype(generator()) > >(n);
  for (auto & x : vec) x = generator();
  auto const merge = merge_id.first;
  auto const id = merge_id.second;
  auto seg = make_segment_tree(n, merge, id);
  rep(i, 0, n)
    { seg.at(i) = vec.at(i); }
  seg.build();
  loop (q) {
    if (rand(0, 1)) {
      auto p = rand(0, n - 1);
      auto x = generator();
      act(vec.at(p), x);
      act(seg.at(p), x);
    } else {
      auto l = rand(0, n - 1), r = rand(0, n - 1);
      if (r < l) std::swap(l, r);
      r++;
      REQUIRE(seg.query(l, r) ==
      std::accumulate(vec.begin() + l, vec.begin() + r, id, merge));
    }
    REQUIRE(seg.collect() == vec);
  }
};

TEMPLATE_TEST_CASE( "segment_tree", "[segment_tree]", int long long ) {
  constexpr auto inf = std::numeric_limits< TestType >::max();
  auto const log_unif_impl = [](auto l, auto r) {
    assert(0 < l && l <= r);
    return TestType(std::pow(2, std::uniform_real_distribution< double >
      (std::log2(l), std::log2(r))(mt)));
  };
  auto const log_unif = [ impl = log_unif_impl ](auto l, auto r) {
      if (0 < l)  return impl(l, r);
      if (l == r) return TestType{l};
      auto const lgl = l == 0 ? 0 : std::log2(-l);
      auto const lgr = r == 0 ? 0 : std::log2(r);
      if (l == 0) return rand(0, lgr) ? impl(1, r) : TestType{0};
      if (r == 0) return rand(0, lgl) ? -impl(1, -l) : TestType{0};
      auto const lg = lgl + lgr + 1;
      auto const t = rand(0, lg - 1);
      if (t < lgl) { return -impl(1, -l); }
      if (t < lgl + lgr) { return impl(1, r); }
      return TestType{0};
  };

  auto const additive_generator = [inf, &log_unif](auto n, auto q) {
    auto const max_max = inf / (n * q);
    TestType const max = log_unif(1, max_max);
    return [max, log_unif]{ return log_unif(-max, max); };
  };

  auto const multiplicative_generator_ = [inf, &log_unif](auto n, auto q) {
    TestType const max = std::pow(inf, -n * q);
    return [max, &log_unif]{ return log_unif(0, max); };
  };

  auto const linear_function_generator_ = [inf, &log_unif](auto n, auto q) {
    TestType const max = std::pow(inf, -n * q);
    return [max, &log_unif]{ return std::make_pair(log_unif(0, max), log_unif(0, max)); };
  };

  auto const inversion_number_generator_ = [inf, &log_unif](auto n, auto q) {
    TestType const max = std::pow(inf, -n * q);
    return [max, &log_unif]{ return std::make_tuple(log_unif(0, max), log_unif(0, max), log_unif(0, max)); };
  };

  auto const sum = std::make_pair([](auto x, auto y){ return x + y; }, TestType{0});
  auto const min = std::make_pair([](auto x, auto y){ return std::min(x, y); }, std::numeric_limits< TestType >::max());
  auto const max = std::make_pair([](auto x, auto y){ return std::max(x, y); }, std::numeric_limits< TestType >::min());
  auto const left = std::make_pair([](auto x, auto y){ return x == -1 ? y : x; }, TestType{-1});
  auto const right = std::make_pair([](auto x, auto y){ return y == -1 ? x : y; }, TestType{-1});
  auto const bitwise_and = std::make_pair([](auto x, auto y){ return x & y; }, TestType{-1});
  auto const bitwise_or = std::make_pair([](auto x, auto y){ return x | y; }, TestType{0});
  auto const bitwise_xor = std::make_pair([](auto x, auto y){ return x | y; }, TestType{0});

  auto const gcd = std::make_pair([](auto x, auto y){ return std::__gcd(x, y); }, TestType{0});
  auto const lcm = std::make_pair([](auto x, auto y){ auto g = std::__gcd(x, y); return g == 0 ? 0 : x / g * y; }, TestType{1});
  auto const prod = std::make_pair([](auto x, auto y){ return x * y;}, TestType{1} );
  auto const cmp = std::make_pair([](auto p, auto q){
      TestType a, b, c, d;
      std::tie(a, b) = p, std::tie(c, d) = q;
      return std::make_pair(a * c, a * d + b);
    },
    std::make_pair(TestType{1}, TestType{0})
  );
  auto const inversion_num_merger = std::make_pair([](auto t0, auto t1){
      TestType x0, y0, z0, x1, y1, z1;
      std::tie(x0, y0, z0) = t0;
      std::tie(x1, y1, z1) = t1;
      return std::make_tuple(x0 + x1, y0 + y1, z0 + z1 + y0 * x1);
    },
    std::make_tuple(TestType{0}, TestType{0}, TestType{0})
  );

  auto const add = [](auto & x, auto y){ x += y; };
  auto const update = [](auto & x, auto y){ x = y; };

  loop(72) {
    config(additive_generator, sum, add);
    config(additive_generator, min, add);
    config(additive_generator, max, add);
    config(additive_generator, sum, update);
    config(additive_generator, min, update);
    config(additive_generator, max, update);
    config(additive_generator, left, update);
    config(additive_generator, right, update);
    config(additive_generator, bitwise_and, update);
    config(additive_generator, bitwise_or, update);
    config(additive_generator, bitwise_xor, update);
    config(multiplicative_generator_, gcd, update);
    config(multiplicative_generator_, lcm, update);
    config(multiplicative_generator_, prod, update);
    config(linear_function_generator_, cmp, update);
    config(inversion_number_generator_, inversion_num_merger, update);
  }
}
