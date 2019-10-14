#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <graph/dijkstra.hpp>
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

template <typename T>
auto make_vector_impl(size_t sz, T t) {return std::vector<T>(sz, t);}

template <size_t N, typename T, typename U, std::enable_if_t<N == 1, std::nullptr_t> = nullptr>
auto make_vector(size_t sz, U u) {return make_vector_impl(sz, T(u));}

template <size_t N, typename T, std::enable_if_t<N == 1, std::nullptr_t> = nullptr>
auto make_vector(size_t sz) {return std::vector<T>(sz);}

template <size_t N, typename T, typename... Args, std::enable_if_t<N != 1, std::nullptr_t> = nullptr>
auto make_vector(size_t a, Args... args) {return make_vector_impl(a, make_vector<N - 1, T>(args...));}

template <typename T, typename Size_t>
auto& at(T& t, Size_t i) {return t.at(i);}

template <typename T, typename Size_t, typename... Args>
auto& at(T& t, Size_t i, Args... args) {return at(t.at(i), args...);}

#define TRIANGULAR_EQ_TEST \
  do {\
    rep(i, 0, n) rep(j, 0, n) rep(k, 0, n) {\
      if (at(dist, i, i) < 0) continue;\
      if (at(dist, j, j) < 0) continue;\
      if (at(dist, k, k) < 0) continue;\
      auto x = at(dist, i, j);\
      auto y = at(dist, i, k);\
      auto z = at(dist, k, j);\
      REQUIRE(x - y <= z);\
    }\
  } while (false)
#define COMPARISON_TEST\
  do {\
    rep(i, 0, n) rep(j, 0, n) {\
      REQUIRE(at(dist, i, j) <= at(adj, i, j));\
    };\
  } while(false)

TEMPLATE_TEST_CASE( "dijkstra", "[dijkstra]", int long long ) {
  constexpr auto inf = std::numeric_limits< TestType >::max();
  loop(72) {
    auto n = rand(1, 20), m = rand(1, (int)(std::pow(n, 1.2)));
    auto adj = make_vector< 2, TestType >(n, n, inf);
    auto graph = make_vector< 2, std::pair< TestType, int > >(n, 0);
    loop(m) {
      auto u = rand(0, n - 1), v = rand(0, n - 1);
      auto x = std::uniform_int_distribution< TestType >(0, inf)(mt);
      cmn(at(adj, u, v), x);
      graph.at(u).emplace_back(x, v);
    }
    auto dist = make_vector< 2, TestType >(n, n);
    rep(i, 0, n) {
      auto const dist_i = dijkstra(graph, i);
      rep(j, 0, n) {
        at(dist, i, j) = dist_i.at(j);
      }
    }
    TRIANGULAR_EQ_TEST;
    COMPARISON_TEST;
  }
}
