#include <catch2/catch.hpp>
#include <algorithm/coenumerate.hpp>
#include <algorithm/enumerate.hpp>

TEST_CASE( "Algorithms on Sequences", "[enumerate, coenumerate]" )
{
  auto sz = 5;
  auto seq = std::vector<int>{10, 11, 12, 13, 14};
  REQUIRE((int)seq.size() == sz);

  SECTION( "coenumerate" )
  {
    auto ret = std::vector<std::pair<int, int>>(sz);
    coenumerate(seq.begin(), seq.end(), ret.begin());
    for (auto i = 0; i < sz; i++)
    {
      REQUIRE(ret.at(i).first  == 10 + i);
      REQUIRE(ret.at(i).second == i);
    }
  }

  SECTION( "enumerate" )
  {
    auto ret = std::vector<std::pair<int, int>>(sz);
    enumerate(seq.begin(), seq.end(), ret.begin());
    for (auto i = 0; i < sz; i++)
    {
      REQUIRE(ret.at(i).first  == i);
      REQUIRE(ret.at(i).second == 10 + i);
    }
  }
}