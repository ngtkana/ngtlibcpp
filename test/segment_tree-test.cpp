#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <segment_tree.hpp>
#define loop(n) for (int ngtkana_is_a_genius = 0; ngtkana_is_a_genius < int(n); ngtkana_is_a_genius++)
#define rep(i, begin, end) for (int i = int(begin); (i) < int(end); i++)
#define all(v) v.begin(), v.end()
#define rand(l, r) std::uniform_int_distribution<>(l, r)(mt)
using lint = long long;
auto mt = std::mt19937_64(std::random_device{}());
auto cmn = [](auto& a, auto b){ if (a > b) {a = b; return true;} return false; };
auto cmx = [](auto& a, auto b){ if (a < b) {a = b; return true;} return false; };
void debug_impl() { std::cerr << std::endl; }
template <typename Head, typename... Tail>
void debug_impl(Head head, Tail... tail) { std::cerr << " " << head; debug_impl(tail...); }
#ifndef STOPIT
#define debug(...)\
  do {\
    std::cerr << std::boolalpha << "[" << #__VA_ARGS__ << "]:";\
    debug_impl(__VA_ARGS__);\
    std::cerr << std::noboolalpha;\
  } while (false)
#else
#define debug(...) 0;
#endif

TEST_CASE( "segment_tree", "[segment_tree]" ) {
  
}