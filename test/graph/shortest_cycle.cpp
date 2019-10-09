#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <graph/shortest_cycle.hpp>
#define loop(n) for (int ngtkana_is_genius = 0; ngtkana_is_genius < int(n); ngtkana_is_genius++)
#define rep(i, begin, end) for(int i = int(begin); i < int(end); i++)
#define all(v) v.begin(), v.end()
#define lint long long
#define rand(l, r) std::uniform_int_distribution<>(l, r)(mt)
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

// Returns {} if has cycle.
inline auto topological_sort(std::vector< std::vector < int > > const & graph) {
  int n = graph.size();
  std::vector< int > ckd(n, 0);
  std::vector< int > sorted{};
  auto dfs = [&] (auto&& f, int crr) -> bool {
    ckd.at(crr) = 1;
    auto ret = false;
    for (auto nxt : graph.at(crr)) {
      if (ckd.at(nxt) == 1) return true;
      if (ckd.at(nxt) == 2) continue;
      ret |= f(f, nxt);
    }
    sorted.emplace_back(crr);
    ckd.at(crr) = 2;
    return ret;
  };
  for (auto i = 0; i < n; i++) {
    if (ckd.at(i) == 0 && dfs(dfs, i))
      { return std::vector< int > {}; }
  }
  std::reverse(sorted.begin(), sorted.end());
  return sorted;
}

TEST_CASE( "Random Sparse Graph", "[shortest_cycle, topological_sort]" ) {
  loop(72) {
    auto mt = std::mt19937(std::random_device{}());
    auto n = rand(2, 60), m = rand(n - 1, std::min(n * (n - 1), 3 * n / 2));
    auto graph = make_vector< 2, int >(n, 0);
    std::set< std::pair< int, int > > set;
    while ((int)set.size() < m) {
      auto u = rand(0, n - 1), v = rand(0, n - 1);
      if (u == v) continue;
      if (!set.emplace(u, v).second) continue;
      graph.at(u).emplace_back(v);
    }
    auto cycle = shortest_cycle(graph);
    auto len = (int)cycle.size();
    rep(i, 0, len) {
      auto x = cycle.at(i);
      auto y = cycle.at(i < len - 1 ? i + 1 : 0);
      REQUIRE(std::count(all(graph.at(x)), y) == 1);
    }

    // Matrix Test
    if (0 < len) {
      REQUIRE(2 <= len);
      auto adj = make_vector< 2, int >(n, n, false);
      for (auto e : set) {
        int u, v; std::tie(u, v) = e;
        at(adj, u, v) = true;
      }
      auto dist = adj;
      loop(len - 2) {
        auto new_dist = make_vector< 2, int >(n, n, false);
        rep(i, 0, n) rep(j, 0, n) rep(k, 0, n) {
          at(new_dist, i, j) |= at(dist, i, k) && at(adj, k, j);
        }
        std::swap(new_dist, dist);
        rep(i, 0, n)
          { REQUIRE(!at(dist, i, i)); }
      }
    }

    // Topo-Sort Test
    REQUIRE((topological_sort(graph).empty() ^ (len == 0)));
  }
}
