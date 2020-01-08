#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <tree/lowest_common_ancestor.hpp>
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

auto const log_unif = [
    impl = [](auto l, auto r) {
      assert(0 < l && l <= r);
      using value_type = std::decay_t< decltype(l) >;
      return value_type(std::pow(2, std::uniform_real_distribution< double >
        (std::log2(l), std::log2(r))(mt)));
    }
  ](auto l, auto r) {
    using value_type = std::decay_t< decltype(l) >;
    if (0 < l)  return impl(l, r);
    if (l == r) return value_type{l};
    auto const lgl = l == 0 ? 0 : std::log2(-l);
    auto const lgr = r == 0 ? 0 : std::log2(r);
    if (l == 0) return rand(0, lgr) ? impl(1, r) : value_type{0};
    if (r == 0) return rand(0, lgl) ? -impl(1, -l) : value_type{0};
    auto const lg = lgl + lgr + 1;
    auto const t = rand(0, lg - 1);
    if (t < lgl) { return -impl(value_type{1}, -l); }
    if (t < lgl + lgr) { return impl(value_type{1}, r); }
    return value_type{0};
};


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

template < class EdgeGenerator, class LabelGenerator >
void config(
    int n,
    EdgeGenerator const & edge_generator,
    LabelGenerator const& label_generator
  )
{
  using label_type = std::decay_t< decltype(label_generator(n)) >;
  auto lca = lowest_common_ancestor< int >(n);
  auto graph = make_vector< 2, std::pair< int, label_type > >(n, 0);
  for (auto const pair : edge_generator(n)) {
    int u, v; std::tie(u, v) = pair;
    auto x = label_generator(n);
    graph.at(u).emplace_back(v, x);
    graph.at(v).emplace_back(u, x);
    lca.insert(u, v, x);
  }

  // build
  auto root = rand(0, n - 1);
  std::vector< std::pair< int, label_type > > prt(n);
  prt.at(root) = std::make_pair(root, 0);
  auto dfs = [&graph, &prt](auto&& f, auto crr, auto p) -> void{
    for (auto const pair : graph.at(crr)) {
      int nxt; label_type x; std::tie(nxt, x) = pair;
      if (nxt == p) continue;
      prt.at(nxt) = std::make_pair(crr, x);
      f(f, nxt, crr);
    }
  };
  dfs(dfs, root, root);
  auto chain = [&prt] (auto x) {
    std::vector< std::pair< int, label_type > > ret{};
    while (true) {
      int p; label_type w; std::tie(p, w) = prt.at(x);
      ret.emplace_back(x, w);
      if (p == x) break;
      x = p;
    }
    std::reverse(all(ret));
    return ret;
  };
  lca.build(root);

  // query
  loop(n) {
    auto u = rand(0, n - 1), v = rand(0, n - 1);
    auto cu = chain(u), cv = chain(v);
    std::vector< std::pair< int, label_type > > meet;
    rep(i, 0, int(std::min(cu.size(), cv.size()))) {
      auto x = cu.at(i), y = cv.at(i);
      if (x == y) meet.emplace_back(x);
    }
    REQUIRE(lca.query(u, v) == meet.back().first);
  }

  // distance
  loop(n) {
    auto u = rand(0, n - 1), v = rand(0, n - 1);
    constexpr auto inf = std::make_pair(
      std::numeric_limits< int >::max(),
      std::numeric_limits< label_type >::max()
    );
    auto dfs = [&graph, u, v, inf](auto&& f, auto crr, auto prv) -> std::pair< int, label_type > {
      auto ret = crr == v ? std::make_pair(0, label_type{0}) : inf;
      for (auto const pair : graph.at(crr)) {
        int nxt; label_type w; std::tie(nxt, w) = pair;
        if (nxt == prv) continue;
        auto reply = f(f, nxt, crr);
        if (reply != inf) {
          ret = reply;
          ret.first += 1;
          ret.second += w;
        }
      }
      return ret;
    };
    int dist; label_type w_dist; std::tie(dist, w_dist) = dfs(dfs, u, u);
    REQUIRE(lca.row_distance(u, v) == dist);
    REQUIRE(lca.weighted_distance(u, v) == w_dist);
  }
}


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

TEMPLATE_TEST_CASE( "unweighted", "[lowest_common_ancestor]", int, long long ) {
  auto const always_one = [](auto n)
    { return TestType{1}; };
  auto const logarithmic = [](auto n) {
    auto const max = std::numeric_limits< TestType >::max() / n;
    return log_unif(0, max);
  };
  loop(12) {
    config(rand(8, 40), random_tree, always_one);
    config(rand(8, 40), high_tree, [](auto n){ return TestType{1}; });
    config(rand(8, 40), high_tree, [](auto n){ return TestType{-1}; });
    config(rand(8, 40), high_tree, [](auto n){ return TestType{rand(0, 1)}; });
    config(rand(8, 40), high_tree, logarithmic);
  }
}
