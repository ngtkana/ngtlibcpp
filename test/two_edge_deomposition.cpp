#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <two_edge_decmoposition.hpp>
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

struct union_find {
  std::vector< int > prt;
  union_find(int n) : prt(n, -1){}
  bool is_root(int i) { return prt.at(i) < 0; }
  int find(int i) { return is_root(i) ? i : prt.at(i) = find(prt.at(i)); }
  int size(int i) { return -prt.at(find(i)); }
  bool is_connected(int i, int j) { return find(i) == find(j); }
  bool connect(int i, int j) {
    if ((i = find(i)) == (j = find(j))) return false;
    if (size(i) > size(j)) std::swap(i, j);
    prt.at(j) += std::exchange(prt.at(i), j);
    return true;
  }
};

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

template < template < typename ... > class Tuple,  typename... Args, std::size_t ... Inds, std::size_t = std::tuple_size< Tuple < Args ... > >::value >
std::istream& tuple_input_impl(std::istream& os, Tuple<Args...>& tuple, std::integer_sequence<std::size_t, Inds...>)
  { (void)std::initializer_list<int>{((void)(os >> std::get< Inds >(tuple)), 0)...}; return os; }
template < template < typename ... > class Tuple,  typename... Args, std::size_t = std::tuple_size< Tuple < Args ... > >::value >
std::istream& operator>> (std::istream& os, Tuple<Args...>& tuple)
  { return tuple_input_impl(os, tuple, std::index_sequence_for<Args...>()); }

template < template < typename ... > class Tuple,  typename... Args, std::size_t ... Inds, std::size_t = std::tuple_size< Tuple < Args ... > >::value >
std::ostream& tuple_output_impl(std::ostream& os, const Tuple<Args...>& tuple, std::integer_sequence<std::size_t, Inds...>)
  { os << "("; (void)std::initializer_list<int>{((void)(os << (Inds > 0 ? "," : "") << std::get< Inds >(tuple)), 0)...}; return os << ")"; }
template < template < typename ... > class Tuple,  typename... Args, std::size_t = std::tuple_size< Tuple < Args ... > >::value >
std::ostream& operator<< (std::ostream& os, const Tuple<Args...>& tuple)
 { return tuple_output_impl(os, tuple, std::index_sequence_for<Args...>()); }

TEST_CASE( "two_edge_decmoposition", "[two_edge_decmoposition]" ) {
  loop(40) {
    std::size_t n = 40, m = rand(n - 1, n * (n - 1) / 2);
    union_find uf(n);
    std::vector< std::vector< int > > graph(n);
    std::set< std::pair< int, int > > edges;
    two_edge_decomposition ted(n);
    std::set< std::pair< int, int > > bridge_set;

    while (edges.size() < m) {
      int u = rand(0, n - 2), v = rand(0, n - 2);
      if (u > v) std::swap(u, v);
      v++;
      if (edges.count({u, v})) continue;
      if (n - 1 <= edges.size() || uf.connect(u, v)) {
        graph.at(u).emplace_back(v);
        graph.at(v).emplace_back(u);
        ted.insert(u, v);
        edges.emplace(u, v);
      }
    }
    ted.build();

    SECTION( "this graph is connected" ) {
      union_find uf(n);
      rep(i, 0, n) {
        for (auto j : graph.at(i)) {
          uf.connect(i, j);
        }
      }
      REQUIRE(uf.size(0) == n);
    }

    SECTION( "bridges contains the inverse edge of each edge" ) {
      std::set< std::pair< int, int > > set{ted.bridges.begin(), ted.bridges.end()};
      for (auto b : ted.bridges) {
        std::swap(b.first, b.second);
        REQUIRE(set.count(b));
      }
    }

    SECTION( "removing a bridge makes the graph disconnected" ) {
      for (auto bridge : ted.bridges) {
        int bi, bj; std::tie(bi, bj) = bridge;
        union_find uf(n);
        rep(i, 0, n) {
          for (int j : graph.at(i)) {
            if ((bi==i && bj==j) || (bi==j && bj==i)) continue;
            uf.connect(i, j);
          }
        }
        REQUIRE(uf.size(0) < n);
      }
    }

    SECTION( "removing all bridges makes a certain family of components" ) {
      union_find uf(n);
      std::set< std::pair< int, int > > set{ted.bridges.begin(), ted.bridges.end()};
      rep(i, 0, n) {
        for (int j : graph.at(i)) {
          if (set.count({i, j})) continue;
          uf.connect(i, j);
        }
      }
      rep(i, 0, n) rep(j, 0, n) {
        REQUIRE((ted.cmp.at(i) == ted.cmp.at(j)) == uf.is_connected(i, j));
      }
    }

    SECTION( "an edge is a bridge iff connects two points of different cmps" ) {
      std::set< std::pair< int, int > > set{ted.bridges.begin(), ted.bridges.end()};
      rep(i, 0, n) {
        for (int j : graph.at(i)) {
          REQUIRE((ted.cmp.at(i) != ted.cmp.at(j)) == bool(set.count({i, j})));
        }
      }
    }
   }
}
