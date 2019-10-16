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

#define ACT_TEST(ACTOR_GENERATOR)\
  do {\
    auto p = rand(0, n - 1);\
    auto x = ACTOR_GENERATOR();\
    act(vec.at(p), x);\
    act(seg.at(p), x);\
    seg.build_oneline(p);\
  } while (false);\


#define QUERY_TEST\
  do {\
    auto l = rand(0, n - 1), r = rand(0, n - 1);\
    if (r < l) std::swap(l, r);\
    r++;\
    REQUIRE(seg.query(l, r) ==\
      std::accumulate(vec.begin() + l, vec.begin() + r, id, merge));\
  } while (false)

#define CONFIG(GENERATOR, MERGE_ID_, ACT_) \
  do {\
    auto const n = rand(1, 8);\
    auto const q = 2 * n;\
    auto const generator = GENERATOR(n, q);\
    auto vec = std::vector< std::decay_t< decltype(generator()) > >(n);\
    for (auto & x : vec) x = generator();\
    auto const merge_id = MERGE_ID_;\
    auto const merge = merge_id.first;\
    auto const id = merge_id.second;\
    auto const act = ACT_;\
    auto seg = make_segment_tree(n, merge, id);\
    rep(i, 0, n)\
      { seg.at(i) = vec.at(i); }\
    seg.build();\
    loop (q) {\
      if (rand(0, 1)) {\
        ACT_TEST(generator);\
      } else {\
        QUERY_TEST;\
      }\
      REQUIRE(seg.collect() == vec);\
    }\
  } while (false)


TEMPLATE_TEST_CASE( "segment_tree", "[segment_tree]", int long long ) {
  constexpr auto inf = std::numeric_limits< TestType >::max();
  auto const test_rand = [](auto l, auto r)
    { return std::uniform_int_distribution< TestType >(l, r)(mt); };

  auto const additive_generator = [inf, &test_rand](auto n, auto q) {
    auto const max = inf / (n * q);
    return [max, &test_rand]{ return test_rand(-max, max); };
  };

  auto const multiplicative_generator = [inf, &test_rand](auto n, auto q) {
    auto const max = std::pow(inf, -n * q);
    return [max, &test_rand]{ return test_rand(0, max); };
  };

  auto const linear_function_generator = [inf, &test_rand](auto n, auto q) {
    auto const max = std::pow(inf, -n * q);
    return [max, &test_rand]{ return std::make_pair(test_rand(0, max), test_rand(0, max)); };
  };

  auto const inversion_number_generator = [inf, &test_rand](auto n, auto q) {
    auto const max = std::pow(inf, -n * q);
    return [max, &test_rand]{ return std::make_tuple(test_rand(0, max), test_rand(0, max), test_rand(0, max)); };
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
    CONFIG(additive_generator, sum, add);
    CONFIG(additive_generator, min, add);
    CONFIG(additive_generator, max, add);
    CONFIG(additive_generator, sum, update);
    CONFIG(additive_generator, min, update);
    CONFIG(additive_generator, max, update);
    CONFIG(additive_generator, left, update);
    CONFIG(additive_generator, right, update);
    CONFIG(additive_generator, bitwise_and, update);
    CONFIG(additive_generator, bitwise_or, update);
    CONFIG(additive_generator, bitwise_xor, update);
    CONFIG(multiplicative_generator, gcd, update);
    CONFIG(multiplicative_generator, lcm, update);
    CONFIG(multiplicative_generator, prod, update);
    CONFIG(linear_function_generator, cmp, update);
    CONFIG(inversion_number_generator, inversion_num_merger, update);
  }
}
