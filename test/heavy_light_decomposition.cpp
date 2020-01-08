// #include <catch2/catch.hpp>
// #include <bits/stdc++.h>
// #include <segment_tree.hpp>
// #define loop(n) for (int ngtkana_is_genius = 0; ngtkana_is_genius < int(n); ngtkana_is_genius++)
// #define rep(i, begin, end) for(int i = int(begin); i < int(end); i++)
// #define all(v) v.begin(), v.end()
// #define rand(l, r) std::uniform_int_distribution<>(l, r)(mt)
// using lint = long long;
// auto mt = std::mt19937_64(std::random_device{}());
// auto cmn = [](auto& a, auto b){if (a > b) {a = b; return true;} return false;};
// auto cmx = [](auto& a, auto b){if (a < b) {a = b; return true;} return false;};
// void debug_impl() { std::cerr << std::endl; }
// template <typename Head, typename... Tail>
// void debug_impl(Head head, Tail... tail){
//   std::cerr << " " << head;
//   debug_impl(tail...);
// }
// #ifndef STOPIT
// #define debug(...)\
//   std::cerr << std::boolalpha << "[" << #__VA_ARGS__ << "]:";\
//   debug_impl(__VA_ARGS__);\
//   std::cerr << std::noboolalpha;
// #else
// #define debug 0;
// #endif

// template < typename Container, typename Value = typename Container::value_type, std::enable_if_t<!std::is_same< Container, std::string >::value, std::nullptr_t> = nullptr>
// std::istream& operator>> (std::istream& is, Container& v)
//   { for (auto & x : v) { is >> x; } return is; }

// template < typename Container, typename Value = typename Container::value_type, std::enable_if_t<!std::is_same< Container, std::string >::value, std::nullptr_t> = nullptr >
// std::ostream& operator<< (std::ostream& os, Container const& v) {
//  os << "{";
//   for (auto it = v.begin(); it != v.end(); it++)
//     {os << (it != v.begin() ? "," : "") << *it;}
//   return os << "}";
// }
// #include <heavy_light_decomposition.hpp>

// template <typename T>
// auto make_vector_impl(size_t sz, T t) {return std::vector<T>(sz, t);}

// template <size_t N, typename T, typename U, std::enable_if_t<N == 1, std::nullptr_t> = nullptr>
// auto make_vector(size_t sz, U u) {return make_vector_impl(sz, T(u));}

// template <size_t N, typename T, std::enable_if_t<N == 1, std::nullptr_t> = nullptr>
// auto make_vector(size_t sz) {return std::vector<T>(sz);}

// template <size_t N, typename T, typename... Args, std::enable_if_t<N != 1, std::nullptr_t> = nullptr>
// auto make_vector(size_t a, Args... args) {return make_vector_impl(a, make_vector<N - 1, T>(args...));}

// template <typename T, typename Size_t>
// auto& at(T& t, Size_t i) {return t.at(i);}

// template <typename T, typename Size_t, typename... Args>
// auto& at(T& t, Size_t i, Args... args) {return at(t.at(i), args...);}

// template < class Merge, class Value, class Generator >
// auto seg_test(
//   int n_max,
//   Merge const &merge,
//   Value id,
//   Generator const& generator_gen
// )
// {
//   auto const n = rand(2, n_max), q = n * n;
//   auto const merge_eq = [&merge](auto & x, auto y){ x = merge(x, y); };
//   auto const generator = generator_gen(n, q);

//   // build graph
//   auto graph = make_vector< 2, int >(n, 0);
//   auto hl = heavy_light_decomposition(n);
//   rep(i, 1, n) {
//     auto u = rand(0, i - 1), v = i;
//     graph.at(u).emplace_back(v);
//     graph.at(v).emplace_back(u);
//     hl.insert(u, v);
//   }
//   hl.build();

//   // build seq
//   std::vector< Value > a(n);
//   for (auto & x : a) x = generator();
//   auto seg = make_segment_tree(n, merge, id);
//   rep(i, 0, n) {
//     seg.at(hl.id(i)) = a.at(i);
//   }
//   seg.build();

//   // query
//   loop(q) {
//     if (rand(0, 1)) {
//       auto p = rand(0, n - 1), x = generator();
//       a.at(p) = x;
//       seg.at(hl.id(p)) = x;
//       seg.build_oneline(hl.id(p));
//     } else {
//       auto u = rand(0, n - 2), v = rand(0, n - 2);
//       if (u > v) std::swap(u, v);
//       v++;
//       Value ans1 = -1;
//       auto const dfs = [&](auto&& f, auto crr, auto prv, auto val) -> void {
//         if (crr == v) ans1 = val;
//         for (auto const nxt : graph.at(crr)) {
//           if (nxt == prv) continue;
//           f(f, nxt, crr, merge(val, a.at(nxt)));
//         }
//       };
//       dfs(dfs, u, u, a.at(u));
//       Value ans2 = id;
//       hl.for_each(u, v, [&merge_eq, &ans2, &seg](auto l, auto r)
//         { merge_eq(ans2, seg.query(l, r)); }, false);
//       REQUIRE(ans1 == ans2);
//     }
//   }
// }

// #define LAMBDA(f) [](auto x, auto y){ return f; }

// TEMPLATE_TEST_CASE( "query", "[HLD]", int, long long) {
//   auto const inf = std::numeric_limits< TestType >::max();
//   auto const additive = [](auto n, auto q) {
//     return [n, q] {
//       auto max = std::numeric_limits< TestType >::max() / n;
//       return std::uniform_int_distribution< TestType >(-max, max)(mt);
//     };
//   };
//   auto const multiplicative = [](auto n, auto q) {
//     return [n, q] {
//       auto max = 6;
//       return std::uniform_int_distribution< TestType >(0, max)(mt);
//     };
//   };

//   std::ignore = GENERATE(take(24, random(0, 0)));
//   SECTION( "range-min ") {
//     seg_test(10, LAMBDA(std::min(x, y)), inf, additive);
//   }

//   SECTION( "range-max ") {
//     seg_test(10, LAMBDA(std::max(x, y)), -inf, additive);
//   }

//   SECTION( "range-sum ") {
//     seg_test(10, LAMBDA(x + y), TestType{0}, additive);
//   }

//   SECTION( "range-gcd ") {
//     seg_test(10, LAMBDA(std::__gcd(x, y)), TestType{0}, multiplicative);
//   }
// }
