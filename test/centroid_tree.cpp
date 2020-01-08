#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <tree/centroid_tree.hpp>
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

TEST_CASE( "centroid_tree", "[centroid_tree]" ) {
  auto mt  = std::mt19937(std::random_device{}());
  loop(20) {
    auto n = rand(20, 20), m = 0;
    auto uf  = union_find(n);
    auto graph = std::vector< std::vector< int > >(n);
    while(true) {
      auto u = rand(0, n - 2), v = rand(0, n - 2);
      if (v < u) std::swap(u, v);
      v++;
      if (uf.unite(u, v)) {
        graph.at(u).emplace_back(v);
        graph.at(v).emplace_back(u);
        if (++m == n - 1)
          { break; }
      }
    }

    auto ctr = centroid_tree(graph);
    ctr.build();

    auto depth    = ctr.get_depth();
    auto size     = ctr.get_size();
    auto subtrees = ctr.get_subtrees();
    auto centroid = ctr.get_centroid();

    SECTION( "top-level test" ) {
      REQUIRE(depth.at(centroid) == 0);
      REQUIRE(size .at(centroid) == n);
    }

    SECTION( "size test" ) {
      auto calc_size = [&] (auto root) {
        auto dfs = [&](auto&& f, auto crr, auto prv) -> int {
          auto ret = 1;
          for (auto nxt : graph.at(crr)) {
            if (nxt == prv || depth.at(nxt) < depth.at(root)) continue;
            ret += f(f, nxt, crr);
          }
          return ret;
        };
        return dfs(dfs, root, root);
      };
      rep(i, 0, n)
        { REQUIRE(calc_size(i) == size.at(i)); }
    }

    SECTION( "depth and subtrees test" ) {
      rep(crr, 0, n) {
        auto sum = 1;
        auto x = size.at(crr);
        for (auto nxt : subtrees.at(crr)) {
          auto y = size.at(nxt);
          REQUIRE(y * 2 <= x);
          REQUIRE(depth.at(crr) + 1 == depth.at(nxt));
          sum += y;
        }
        REQUIRE(sum == x);
      }
    }
  }
}
