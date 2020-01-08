// #include <catch2/catch.hpp>
// #include <bits/stdc++.h>
// #include <trie.hpp>
// #include "../utility.hpp"

// #define loop(n) for (int ngtkana_is_genius = 0; ngtkana_is_genius < int(n); ngtkana_is_genius++)
// #define rep(i, begin, end) for(int i = int(begin); i < int(end); i++)
// #define all(v) v.begin(), v.end()
// #define rand(l, r) std::uniform_int_distribution<>(l, r)(mt)
// #define lint long long
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

// TEST_CASE( "Trie Tests", "[Trie]" ) {
//   loop(8) {
//     std::mt19937 mt(std::random_device{}());
//     auto k    = rand(1, 5);
//     auto trie = make_trie(k, [](auto x){ return x - '0'; });

//     std::multiset< std::string > set;
//     loop(24) {
//       auto n = rand(3, 6);
//       std::string s(n, '0' + rand(0, k - 1));
//       trie.insert(s);
//       set.insert(s);
//     }

//     SECTION( "count, prefices" ) {
//       loop(24) {
//         auto n = rand(3, 6);
//         std::string s(n, '0' + rand(0, k - 1));
//         REQUIRE(trie.count(s) == set.count(s));

//         std::vector< int > cnt(n + 1, 0);
//         for (auto pair : trie.find_prefices(s))
//           { cnt.at(pair.first)++; }
//         rep(i, 1, n + 1)
//           { REQUIRE(cnt.at(i) == set.count(std::string(s.begin(), s.begin() + i))); }
//       }
//     }

//     SECTION( "depth of nodes" ) {
//       auto seq = trie.get();
//       REQUIRE(seq.front().depth() == 0);
//       for (auto x : seq) {
//         for (auto j : x.get_nexts()) {
//           if (j == -1) continue;
//           auto y = seq.at(j);
//           REQUIRE(x.depth() + 1 == y.depth());
//         }
//       }
//     }
//   }
// }
