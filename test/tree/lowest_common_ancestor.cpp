#include <catch2/catch.hpp>
#include <bits/stdc++.h>
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
#include <tree/lowest_common_ancestor.hpp>

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

class union_find {
    int n;
    std::vector<int> prt;

  public:
    union_find (int n) : n(n), prt(n, -1){}

    bool is_root (int x)        const {return prt.at(x) < 0;}
    int  size    (int x)        const {return -prt.at(find(x));}
    bool same(int x, int y)     const {return find(x) == find(y);}
    int  find    (int x)        const {
      while (!is_root(x)) x = prt.at(x);
      return x;
    }
    // Returns `true` if x and y are newly connected.
    // The smaller one x becomes a child of the larger one y.
    bool unite   (int x, int y) {
      if ((x = find(x)) == (y = find(y))) return false;
      if (size(x) > size(y)) std::swap(x, y);
      prt.at(y) += prt.at(x);
      prt.at(x) = y;
      return true;
    }
};

template < class Generator >
void config(int n, Generator const & generator) {
  auto lca = lowest_common_ancestor< int >(n);
  auto graph = make_vector< 2, int >(n, 0);
  for (auto const pair : generator(n)) {
    int u, v; std::tie(u, v) = pair;
    graph.at(u).emplace_back(v);
    graph.at(v).emplace_back(u);
    lca.insert(u, v);
  }

  // build
  auto root = rand(0, n - 1);
  std::vector< int > prt(n, -1);
  prt.at(root) = root;
  auto dfs = [&graph, &prt](auto&& f, auto crr, auto p) -> void{
    for (auto const nxt : graph.at(crr)) {
      if (nxt == p) continue;
      prt.at(nxt) = crr;
      f(f, nxt, crr);
    }
  };
  dfs(dfs, root, root);
  auto chain = [&prt] (auto x) {
    std::vector< int > ret{};
    while (true) {
      ret.emplace_back(x);
      auto p = prt.at(x);
      if (p == x) break;
      x = p;
    }
    std::reverse(all(ret));
    return ret;
  };
  lca.build(root);

  // query
  auto q = n;
  loop(q) {
    auto u = rand(0, n - 1), v = rand(0, n - 1);
    auto cu = chain(u), cv = chain(v);
    std::vector< int > meet;
    rep(i, 0, int(std::min(cu.size(), cv.size()))) {
      auto x = cu.at(i), y = cv.at(i);
      if (x == y) meet.emplace_back(x);
    }
    REQUIRE(lca.query(u, v) == meet.back());
  }
}

TEST_CASE( "LCA", "[lowest_common_ancestor]" ) {
  auto const random_tree = [](auto n) {
    auto uf = union_find(n);
    auto m = 0;
    std::vector< std::pair< int, int > > ret;
    while (true) {
      auto u = rand(0, n - 2), v = rand(0, n - 2);
      if (u < v) std::swap(u, v);
      v++;
      if (uf.unite(u, v)) {
        ret.emplace_back(u, v);
        if (++m == n - 1) break;
      }
    }
    return ret;
  };

  auto const high_tree = [inf = std::numeric_limits< double >::infinity()](auto n) {
    std::vector< double > wt(n, 0);
    std::vector< double > distribution(n, inf);
    distribution.at(0) = 0;
    double max = 0;
    std::vector< std::pair< int, int > > ret;
    rep(i, 1, n) {
      int p = std::lower_bound(
          all(distribution),
          std::uniform_real_distribution< double >(0, max)(mt)
        )
        - distribution.begin();
      cmn(p, i - 1);
      auto d = wt.at(i) = (wt.at(p) + std::numeric_limits< double >::min()) * 300;
      max = distribution.at(i) = max + d;
      ret.emplace_back(p, i);
    }
    return ret;
  };

  loop(24) {
    config(rand(8, 120), random_tree);
    config(rand(8, 120), high_tree);
  }
}
