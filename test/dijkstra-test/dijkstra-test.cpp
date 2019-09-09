#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <graph/dijkstra.hpp>

constexpr int inf = std::numeric_limits< int >::max();

struct dijkstra_tag{};

template < typename DispatchTag >
struct engine{};

template <>
struct engine< dijkstra_tag >{
  dijkstra< int > dij;
  engine(int n, int start) : dij(n, start, inf){}
  auto insert(int i, int j, int cost){ dij.insert(i, j, cost); }
  void build() { return dij.build(); }
  auto at(int i) { return dij.at(i); }
};

TEMPLATE_TEST_CASE( "Dijkstra Test", "[dijkstra]",
  dijkstra_tag
)
{
  engine< TestType > engine(4, 0);
  engine.insert(0, 1, 10);
  engine.insert(0, 2, 30);
  engine.insert(1, 3, 20);
  engine.insert(1, 3, 10);
  engine.build();
  REQUIRE( engine.at(0) ==  0 );
  REQUIRE( engine.at(1) == 10 );
  REQUIRE( engine.at(2) == 30 );
  REQUIRE( engine.at(3) == 20 );
}