#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <sqrt_decomposition.hpp>
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

auto mt = std::mt19937_64(std::random_device{}());
TEMPLATE_TEST_CASE( "Sqrt Decomposition", "[sqrt_decomposition]", int, long long ) {
  constexpr auto inf = std::numeric_limits< TestType >::max();
  loop(24) {
    auto n = rand(2, 40);
    std::vector< TestType > a(n);
    for (auto & x : a) x = std::uniform_int_distribution< TestType >(0, inf)(mt);

    // prepare sqrt_decompositon
    auto sd = sqrt_decomposition(n, std::sqrt(n));
    auto m  = sd.get_block_number();
    auto sz = sd.get_block_size();
    std::vector< TestType > range_min(m, inf);
    rep(i, 0, n)
      { cmn(range_min.at(i / sz), a.at(i)); }

    // query
    loop(100) {
      // update
      if (rand(0, 1)) {
        auto i = rand(0, n - 1);
        auto x = std::uniform_int_distribution< TestType >(0, inf)(mt);
        a.at(i) = x;
        auto j = i / sz;
        auto & crr = range_min.at(j);
        crr = inf;
        rep(k, j * sz, std::min(n, (j + 1) * sz))
          { cmn(crr, a.at(k)); }
      }

      // range-min
      else {
        auto l = rand(0, n - 2), r = rand(0, n - 2);
        if (r < l) std::swap(l, r);
        r++;
        auto ret0 = inf;
        sd.query(l, r,
          [&](auto i, auto){ cmn(ret0, a.at(i)); },
          [&](auto j){ cmn(ret0, range_min.at(j)); }
        );
        auto ret1 = inf;
        rep(i, l, r)
          { cmn(ret1, a.at(i)); }
        REQUIRE(ret0 == ret1);
      }
    }
  }
}
