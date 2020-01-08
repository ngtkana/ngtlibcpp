#include <catch2/catch.hpp>
#include <bits/stdc++.h>

#define loop(h) for (int ngtkana_is_genius = 0; ngtkana_is_genius < int(h); ngtkana_is_genius++)
#define rep(i, begin, end) for(int i = int(begin); i < int(end); i++)
#define all(v) v.begin(), v.end()
#define lint long long
auto cmn = [](auto& a, auto b){if (a > b) {a = b; return true;} return false;};
auto cmx = [](auto& a, auto b){if (a < b) {a = b; return true;} return false;};
  void debug_impl() { std::cerr << std::endl; }
  template <typename Head, typename... Tail>
  void debug_impl(Head head, Tail... tail){
    std::cerr << " " << head;
    debug_impl(tail...);
  }
  #define debug(...)\
    std::cerr << std::boolalpha << "[" << #__VA_ARGS__ << "]:";\
    debug_impl(__VA_ARGS__);\
    std::cerr << std::noboolalpha;
  #define rand(l, r) std::uniform_int_distribution<int>(l, r)(mt)

  #include <wavelet_matrix.hpp>

  template <typename T>
  std::istream& operator>> (std::istream& is, std::vector<T>& v) {
    for (auto & x : v) is >> x;
    return is;
  }

  template <typename T>
  std::ostream& operator<< (std::ostream& os, const std::vector<T>& v) {
    auto h = v.size();
    os << "{";
    for (size_t i = 0; i < h; i++)
      {os << (i > 0 ? "," : "") << v.at(i);}
    return os << "}";
  }


std::mt19937_64 mt(std::random_device{}());

TEST_CASE( "Fully Indexible Dictionary Test", "[fully_indexable_dictionary]" ) {
  std::ignore = GENERATE(take(20, random(0, 1)));

  const auto h = 100;
  auto a = std::vector< int >(h);
  std::generate(a.begin(), a.end(), []{ return rand(0, 1); });

  std::vector< int > b(h, 0);
  rep(i, 1, h) {
    b.at(i) = b.at(i - 1) + a.at(i - 1);
  }

  std::vector< int > c{};
  rep(i, 0, h) {
    if (a.at(i))
      { c.emplace_back(i); }
  }

  auto fid = fully_indexable_dictionary(h);
  rep(i, 0, h) {
    if (a.at(i))
      { fid.set(i); }
  }
  fid.build();

  loop(24) {
    auto k = rand(0, h - 1);
    REQUIRE(fid.rank(k, 1) == b.at(k));
  }
  loop(24) {
    auto k = rand(0, h - 1);
    REQUIRE(fid.select(k, 1) == (k >= (int)c.size() ? h : c.at(k)));
  }
}

TEST_CASE( "Wavelet Matrix Test", "[wavelet_matrix]" ) {
  auto h      = 1000;
  auto max    = 100;
  auto mulmax = 50;
  auto a = std::vector< int >(h);
  std::generate(a.begin(), a.end(), [max]{ return rand(0, max - 1); });

  std::vector< int > b(h, 0);
  rep(i, 1, h) {
    b.at(i) = b.at(i - 1) + a.at(i - 1);
  }
  auto wm = wavelet_matrix< int >(a, 30);

  SECTION( "access" ) {
    loop(24) {
      auto k = rand(0, h - 1);
      REQUIRE(wm.access(k) == a.at(k));
    }
  }
  SECTION( "rank" ) {
    loop(24) {
      auto l = rand(0, h - 1);
      auto r = rand(0, h - 1);
      auto x = rand(0, max - 1);
      if (r < l) std::swap(l, r);
      r++;
      auto ret = 0;
      rep(i, l, r)
        { ret += a.at(i) == x; }
      REQUIRE(wm.rank(l, r, x) == ret);
    }
  }
  SECTION( "select" ) {
    loop(24) {
      auto k      = rand(0, mulmax - 1);
      auto x      = rand(0, h - 1);
      auto offset = rand(0, max - 1);
      auto cnt = 0;
      auto ret = h;
      rep(i, offset, h) {
        if (a.at(i) == x && ++cnt == k) break;
      }
      REQUIRE(wm.select(k, x, offset) == ret);
    }
  }
  SECTION( "quantitile" ) {
    loop(24) {
      auto l = rand(0, h - 1);
      auto r = rand(0, h - 1);
      if (r < l) std::swap(l, r);
      r++;
      auto k = rand(0, std::min(r - l, mulmax) - 1);
      std::vector< int > buf(a.begin() + l, a.begin() + r);
      std::sort(all(buf));
      std::reverse(all(buf));
      REQUIRE(wm.quantile(l, r, k) == buf.at(k));
    }
  }
  SECTION( "rangefreq" ) {
    loop(24) {
      auto l = rand(0, h - 1);
      auto r = rand(0, h - 1);
      if (r < l) std::swap(l, r);
      r++;
      auto lwr = rand(0, max - 1);
      auto upr = rand(0, max - 1);
      if (upr < lwr) std::swap(lwr, upr);
      upr++;
      auto ret = 0;
      rep(i, l, r) {
        if (lwr <= a.at(i) && a.at(i) < upr) ret++;
      }
      REQUIRE(wm.rangefreq(l, r, lwr, upr) == ret);
    }
  }
}