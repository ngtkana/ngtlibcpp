#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <algorithm/runlength.hpp>
#define rep(i, begin, end) for(int i = int(begin); i < int(end); i++)
#define loop(h) for (int ngtkana_is_genius = 0; ngtkana_is_genius < int(h); ngtkana_is_genius++)
#define all(v) v.begin(), v.end()
#define rand(l, r) std::uniform_int_distribution<int>(l, r)(mt)
auto cmn = [](auto& a, auto b){if (a > b) {a = b; return true;} return false;};
auto cmx = [](auto& a, auto b){if (a < b) {a = b; return true;} return false;};

std::mt19937_64 mt(std::random_device{}());

template <typename T>
std::istream& operator>> (std::istream& is, std::vector<T>& v) {
  for (auto & x : v) is >> x;
  return is;
}

template <typename T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& v) {
  auto n = v.size();
  os << "{";
  for (size_t i = 0; i < n; i++)
    {os << (i > 0 ? "," : "") << v.at(i);}
  return os << "}";
}

template <typename T, typename U>
std::ostream& operator<< (std::ostream& os, const std::pair<T, U>& pair)
  { return os << "(" << pair.first << "," << pair.second << ")"; }

template <typename T, typename U>
std::istream& operator>> (std::iostream& is, std::pair<T, U>& pair)
  { return is >> pair.first >> pair.second; }

TEMPLATE_TEST_CASE( "runlength", "[runlength]", int, long long ) {
  auto nmax = 20;
  loop(24) {
    auto n = rand(1, nmax);
    std::vector< TestType > a(n);
    for (auto & x : a) x = rand(1, (n + 2) / 3);
    std::sort(all(a));
    auto rle = runlength(a);

    // compare with random access
    std::vector< int > mul(rle.size());
    std::transform(all(rle), mul.begin(), [](auto const p){ return p.second; });
    std::partial_sum(all(mul), mul.begin());
    rep(i, 0, n) {
      auto j = std::upper_bound(all(mul), i) - mul.begin();
      REQUIRE(a.at(i) == rle.at(j).first);
    }
  }
}
