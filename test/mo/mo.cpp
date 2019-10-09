#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <mo/mo.hpp>
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

auto mt = std::mt19937_64(std::random_device{}());
TEST_CASE( "Mo's Algorighm", "[Mo's Algorighm]" ) {
  SECTION( "Kinds Query" ) {
    loop(24) {
      // generate
      auto n = rand(2, 30), q = rand(1, 30), max = rand(1, 30);
      auto a = std::vector< int >(n);
      for (auto & x : a) x = rand(0, max);
      auto queries = std::vector< std::pair< int, int > >(q);
      for (auto & pair : queries) {
        auto l = rand(0, n - 2), r = rand(0, n - 2);
        if (r < l) std::swap(l, r);
        r++;
        pair = {l, r};
      }

      // execute
      auto mo = mo_algorithm(n, q, std::max(1, int(n / std::sqrt(q))));
      rep(i, 0, q) {
        int l, r; std::tie(l, r) = queries.at(i);
        mo.set(i, l, r);
      }
      mo.build();
      std::vector< int > mul(max + 1, 0);
      auto now = 0;
      std::vector< int > ans(q);
      mo.run(
        [&a, &mul, &now](auto i){
          if (mul.at(a.at(i))++ == 0)
            { now++; }
        },
        [&a, &mul, &now](auto i){
          if (--mul.at(a.at(i)) == 0)
            { now--; }
        },
        [&now, &ans](int i){ ans.at(i) = now; }
      );

      // verify
      rep(i, 0, q) {
        int l, r; std::tie(l, r) = queries.at(i);
        std::vector< int > mul(max + 1, 0);
        rep(j, l, r)
          { mul.at(a.at(j))++; }
        auto kinds = std::count_if(all(mul), [](auto x){ return 0 < x; });
        REQUIRE(ans.at(i) == kinds);
      }
    }
  }

  SECTION( "Multiplicity-of-Mode Query" ) {
    loop(24) {
      // generate
      auto n = rand(2, 30), q = rand(1, 30), max = rand(1, 30);
      auto a = std::vector< int >(n);
      for (auto & x : a) x = rand(0, max);
      auto queries = std::vector< std::pair< int, int > >(q);
      for (auto & pair : queries) {
        auto l = rand(0, n - 2), r = rand(0, n - 2);
        if (r < l) std::swap(l, r);
        r++;
        pair = {l, r};
      }

      // execute
      auto mo = mo_algorithm(n, q, std::max(1, int(n / std::sqrt(q))));
      rep(i, 0, q) {
        int l, r; std::tie(l, r) = queries.at(i);
        mo.set(i, l, r);
      }
      mo.build();
      std::vector< int > mul(max + 1, 0);
      std::vector< int > reach(n + 1, 0);
      auto now = 0;
      std::vector< int > ans(q);
      mo.run(
        [&a, &mul, &reach, &now](auto i){
          auto & m = mul.at(a.at(i));
          --reach.at(m);
          ++m;
          ++reach.at(m);
          if (now < m)
            { ++now; }
        },
        [&a, &mul, &reach, &now](auto i){
          auto & m = mul.at(a.at(i));
          --reach.at(m);
          if (reach.at(m) == 0 && now == m)
            { --now; }
          --m;
          ++reach.at(m);
        },
        [&now, &ans](int i){ ans.at(i) = now; }
      );

      // verify
      rep(i, 0, q) {
        int l, r; std::tie(l, r) = queries.at(i);
        std::vector< int > mul(max + 1, 0);
        rep(j, l, r)
          { mul.at(a.at(j))++; }
        auto mul_of_mode = *std::max_element(all(mul));
        REQUIRE(mul_of_mode != -1);
        REQUIRE(ans.at(i) == mul_of_mode);
      }
    }
  }
}
