#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <algorithm/coenumerate.hpp>
#include <algorithm/enumerate.hpp>
#include <algorithm/zip2.hpp>
#include <algorithm/zip.hpp>
#include <algorithm/compress.hpp>
#include <algorithm/runlength.hpp>

#define rep(i, begin, end) for(int i = int(begin); i < int(end); i++)
#define loop(h) for (int ngtkana_is_genius = 0; ngtkana_is_genius < int(h); ngtkana_is_genius++)
#define all(v) v.begin(), v.end()
#define rand(l, r) std::uniform_int_distribution<int>(l, r)(mt)
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

TEST_CASE( "Algorithms on Sequences", "[enumerate, coenumerate, zip]" ) {
  auto nmax    = 20;
  auto max     = 1'000'000'000;

  SECTION( "coenumerate" ) {
    loop(24) {
      auto n = rand(1, nmax);
      std::vector< int > a(n);
      for (auto & x : a) x = rand(1, max);
      auto const ret = coenumerate(a);
      auto i = rand(0, n - 1);
      REQUIRE(ret.at(i).first  == a.at(i));
      REQUIRE(ret.at(i).second == i);
    }
  }
  SECTION( "enumerate" ) {
    loop(24) {
      auto n = rand(1, nmax);
      std::vector< int > a(n);
      for (auto & x : a) x = rand(1, max);
      auto const ret = enumerate(a);
      auto i = rand(0, n - 1);
      REQUIRE(ret.at(i).first  == i);
      REQUIRE(ret.at(i).second == a.at(i));
    }
  }
  SECTION( "zip2" ) {
    loop(24) {
      auto n = rand(1, nmax);
      std::vector< int > a(n), b(n);
      for (auto & x : a) x = rand(1, max);
      for (auto & x : b) x = rand(1, max);
      auto const ret = zip2(a, b);
      auto i = rand(0, n - 1);
      REQUIRE(ret.at(i).first  == a.at(i));
      REQUIRE(ret.at(i).second == b.at(i));
    }
  }
  SECTION( "zip2" ) {
    loop(24) {
      auto n = rand(1, nmax);
      std::vector< int > a(n), b(n), c(n);
      for (auto & x : a) x = rand(1, max);
      for (auto & x : b) x = rand(1, max);
      for (auto & x : c) x = rand(1, max);
      auto const ret = zip(a, b, c);
      auto i = rand(0, n - 1);
      REQUIRE(std::get< 0 >(ret.at(i)) == a.at(i));
      REQUIRE(std::get< 1 >(ret.at(i)) == b.at(i));
      REQUIRE(std::get< 2 >(ret.at(i)) == c.at(i));
    }
  }
  SECTION( "compress" ) {
    loop(24) {
      auto n = rand(1, nmax);
      std::vector< int > a(n);
      for (auto & x : a) x = rand(1, n);
      auto ret = compress(a);
      loop(n) {
        auto i = rand(0, n - 1);
        auto j = rand(0, n - 1);
        REQUIRE((a.at(i) < a.at(j)) == (ret.at(i) < ret.at(j)));
      }
      std::sort(all(a));
      std::sort(all(ret));
      a.resize(std::unique(all(a)) - a.begin());
      ret.resize(std::unique(all(ret)) - ret.begin());
      REQUIRE(a.size() == ret.size());
      REQUIRE((int)ret.size() - 1 == ret.back());
    }
  }
  SECTION( "runlength" ) {
    loop(24) {
      auto n = rand(1, nmax);
      std::vector< int > a(n);
      for (auto & x : a) x = rand(1, nmax);
      std::sort(all(a));
      auto ret = runlength(a);
      loop(n) {
        auto i = rand(0, n - 1);
        auto j = 0;
        auto y = -1;
        for (auto pair : ret) {
          int value, mul; std::tie(value, mul) = pair;
          if (i < j + mul) {
            y = value;
            break;
          }
          j += mul;
        }
        REQUIRE(a.at(i) == y);
      }
    }
  }
}
