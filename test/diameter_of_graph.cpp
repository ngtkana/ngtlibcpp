#include <catch2/catch.hpp>
#include <bits/stdc++.h>
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
#include <diameter_floyd_warshall.hpp>
#include <diameter_dijkstra.hpp>
#include <diameter_bfs.hpp>

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

TEMPLATE_TEST_CASE( "diameter", "[diameter]", int, lint) {
  auto mt = std::mt19937(std::random_device{}());
  auto inf = std::numeric_limits< TestType >::max();
  loop(24) {
    auto n = rand(5, 20);
    auto a = make_vector< 2, TestType > (n, n, 0);
    rep(i, 0, n) rep(j, i + 1, n) {
      TestType x = rand(0, 1);
      if (x == 0) x = inf;
      at(a, i, j) = at(a, j, i) = x;
    }

    // add tree
    auto uf = union_find(n);
    auto m = 0;
    while (true) {
      auto u = rand(0, n - 2), v = rand(0, n - 2);
      if (v < u) std::swap(u, v);
      v++;
      if (uf.unite(u, v)) {
        at(a, u, v) = at(a, v, u) = 1;
        if (++m == n - 1)
          { break; }
      }
    }

    // check componentdness
    std::vector< int > ckd(n, false);
    auto dfs = [&] (auto&& f, auto crr, auto prv) -> void {
      ckd.at(crr) = true;
      rep(nxt, 0, n) {
        if (nxt != prv && at(a, crr, nxt) && !ckd.at(nxt)) {
          f(f, nxt, crr);
        }
      }
    };
    dfs(dfs, 0, 0);
    REQUIRE(std::all_of(all(ckd), [](auto x){ return x; }));

    // transform to the adjacency list
    auto graph = make_vector< 2, int >(n, 0);
    auto weighted_graph = make_vector< 2, std::pair< int, TestType > >(n, 0);
    rep(i, 0, n) rep(j, i + 1, n) {
      auto x = at(a, i, j);
      if (x != inf) {
        graph.at(i).emplace_back(j);
        graph.at(j).emplace_back(i);
        weighted_graph.at(i).emplace_back(j, x);
        weighted_graph.at(j).emplace_back(i, x);
      }
    }

    // calc diam
    auto diam_floyd_warshall = diameter_floyd_warshall(a);
    auto diam_dijkstra       = diameter_dijkstra(weighted_graph);
    auto diam_bfs            = diameter_bfs(graph);
    auto diam                = diam_floyd_warshall;
    REQUIRE(diam == diam_dijkstra);
    REQUIRE(diam == diam_bfs);
  }
}
