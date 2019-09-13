#include <catch2/catch.hpp>
#include <algorithm/coenumerate.hpp>
#include <algorithm/enumerate.hpp>
#include <algorithm/zip2.hpp>
#include <algorithm/zip.hpp>

TEST_CASE( "Algorithms on Sequences", "[enumerate, coenumerate]" ) {
  auto sz = 5;
  auto seq1 = std::vector<int>(sz);
  auto seq2 = std::vector<int>(sz);
  auto seq3 = std::vector<int>(sz);
  auto seq4 = std::vector<int>(sz);
  std::iota(seq1.begin(), seq1.end(), 10);
  std::iota(seq2.begin(), seq2.end(), 20);
  std::iota(seq3.begin(), seq3.end(), 30);
  std::iota(seq4.begin(), seq4.end(), 40);

  SECTION( "coenumerate" ) {
    auto const ret = coenumerate(seq1);
    for (auto i = 0; i < sz; i++) {
      REQUIRE(ret.at(i).first  == 10 + i);
      REQUIRE(ret.at(i).second == i);
    }
  }

  SECTION( "enumerate" ) {
    auto const ret = enumerate(seq1);
    for (auto i = 0; i < sz; i++) {
      REQUIRE(ret.at(i).first  == i);
      REQUIRE(ret.at(i).second == 10 + i);
    }
  }

  SECTION( "zip 2" ) {
    auto const ret = zip2(seq1, seq2);
    for (auto i = 0; i < sz; i++) {
      REQUIRE(ret.at(i).first  == 10 + i);
      REQUIRE(ret.at(i).second == 20 + i);
    }
  }

  SECTION( "1-fold zip" ) {
    auto const ret = zip(seq1);
    for (auto i = 0; i < sz; i++) {
      REQUIRE(std::get<0>(ret.at(i)) == 10 + i);
    }
  }

  SECTION( "2-fold zip" ) {
    auto const ret = zip(seq1, seq2);
    for (auto i = 0; i < sz; i++) {
      REQUIRE(std::get<0>(ret.at(i)) == 10 + i);
      REQUIRE(std::get<1>(ret.at(i)) == 20 + i);
    }
  }

  SECTION( "3-fold zip" ) {
    auto const ret = zip(seq1, seq2, seq3);
    for (auto i = 0; i < sz; i++) {
      REQUIRE(std::get<0>(ret.at(i)) == 10 + i);
      REQUIRE(std::get<1>(ret.at(i)) == 20 + i);
      REQUIRE(std::get<2>(ret.at(i)) == 30 + i);
    }
  }

  SECTION( "4-fold zip" ) {
    auto const ret = zip(seq1, seq2, seq3, seq4);
    for (auto i = 0; i < sz; i++) {
      REQUIRE(std::get<0>(ret.at(i)) == 10 + i);
      REQUIRE(std::get<1>(ret.at(i)) == 20 + i);
      REQUIRE(std::get<2>(ret.at(i)) == 30 + i);
      REQUIRE(std::get<3>(ret.at(i)) == 40 + i);
    }
  }

}