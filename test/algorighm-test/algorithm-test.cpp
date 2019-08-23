#include <catch2/catch.hpp>
#include <algorithm/coenumerate.hpp>
#include <algorithm/enumerate.hpp>
#include <algorithm/zip2.hpp>
#include <algorithm/zip3.hpp>
#include <algorithm/zip4.hpp>

TEST_CASE( "Algorithms on Sequences", "[enumerate, coenumerate]" )
{
  auto sz = 5;
  auto seq1 = std::vector<int>(sz);
  auto seq2 = std::vector<int>(sz);
  auto seq3 = std::vector<int>(sz);
  auto seq4 = std::vector<int>(sz);
  std::iota(seq1.begin(), seq1.end(), 10);
  std::iota(seq2.begin(), seq2.end(), 20);
  std::iota(seq3.begin(), seq3.end(), 30);
  std::iota(seq4.begin(), seq4.end(), 40);

  SECTION( "coenumerate" )
  {
    auto ret = std::vector<std::pair<int, int>>(sz);
    coenumerate(seq1.begin(), seq1.end(), ret.begin());
    for (auto i = 0; i < sz; i++)
    {
      REQUIRE(ret.at(i).first  == 10 + i);
      REQUIRE(ret.at(i).second == i);
    }
  }

  SECTION( "enumerate" )
  {
    auto ret = std::vector<std::pair<int, int>>(sz);
    enumerate(seq1.begin(), seq1.end(), ret.begin());
    for (auto i = 0; i < sz; i++)
    {
      REQUIRE(ret.at(i).first  == i);
      REQUIRE(ret.at(i).second == 10 + i);
    }
  }

  SECTION( "zip 2" )
  {
    auto ret = std::vector<std::pair<int, int>>(sz);
    zip2(seq1.begin(), seq1.end(), seq2.begin(), ret.begin());
    for (auto i = 0; i < sz; i++)
    {
      REQUIRE(ret.at(i).first  == 10 + i);
      REQUIRE(ret.at(i).second == 20 + i);
    }
  }

  SECTION( "zip 3" )
  {
    auto ret = std::vector<std::tuple<int, int, int>>(sz);
    zip3(seq1.begin(), seq1.end(), seq2.begin(), seq3.begin(), ret.begin());
    for (auto i = 0; i < sz; i++)
    {
      REQUIRE(std::get<0>(ret.at(i)) == 10 + i);
      REQUIRE(std::get<1>(ret.at(i)) == 20 + i);
      REQUIRE(std::get<2>(ret.at(i)) == 30 + i);
    }
  }

  SECTION( "zip 4" )
  {
    auto ret = std::vector<std::tuple<int, int, int, int>>(sz);
    zip4(seq1.begin(), seq1.end(), seq2.begin(), seq3.begin(), seq4.begin(), ret.begin());
    for (auto i = 0; i < sz; i++)
    {
      REQUIRE(std::get<0>(ret.at(i)) == 10 + i);
      REQUIRE(std::get<1>(ret.at(i)) == 20 + i);
      REQUIRE(std::get<2>(ret.at(i)) == 30 + i);
      REQUIRE(std::get<3>(ret.at(i)) == 40 + i);
    }
  }

}