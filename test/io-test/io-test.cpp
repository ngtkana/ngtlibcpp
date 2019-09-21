#include <catch2/catch.hpp>
#include <io/tuple_io.hpp>
#include <io/pair_io.hpp>
#include <io/container_io.hpp>
#include <sstream>
#include <iterator>
#include <iostream>

TEST_CASE("tuple io", "[tuple_io]")
{
  std::stringstream ss;
  ss << 10 << std::endl
     << 'c' << std::endl;
  std::tuple<int, char> tuple;
  ss >> tuple;
  REQUIRE(std::get<0>(tuple) == 10);
  REQUIRE(std::get<1>(tuple) == 'c');
  ss.str("");
  ss.clear(std::stringstream::goodbit);
  ss << tuple;
  REQUIRE(ss.str() == "(10,c)");
}

TEST_CASE("pair io", "[pair_io]")
{
  std::stringstream ss;
  ss << 10 << std::endl
     << 'c' << std::endl;
  std::pair<int, char> pair;
  ss >> pair;
  REQUIRE(pair.first  == 10);
  REQUIRE(pair.second == 'c');
  ss.str("");
  ss.clear(std::stringstream::goodbit);
  ss << pair;
  REQUIRE(ss.str() == "(10,c)");
}

TEST_CASE("vector io", "[vector_io]")
{
  int n = 5;
  std::stringstream ss;
  for (auto i = 0; i < n; i++)
  {
    ss << 10 + i << std::endl;
  }
  std::vector<int> v(n);
  ss >> v;
  for (auto i = 0; i < n; i++)
  {
    REQUIRE(v.at(i) == 10 + i);
  }
  ss.str("");
  ss.clear(std::stringstream::goodbit);
  ss << v;
  REQUIRE(ss.str() == "{10,11,12,13,14}");
}
