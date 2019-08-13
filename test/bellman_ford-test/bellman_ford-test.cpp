#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <combinator/combinator.hpp>
#include <generic_graphs/graph.hpp>
#include <generic_graphs/bellman_ford.hpp>

TEST_CASE("Sample Test 1 from ABC137-E.", "[Bellman-Ford]")
{
  auto g = bellman_ford<int>(3);
  g.insert_directed_edge(0, 1, -10);
  g.insert_directed_edge(1, 2, -20);
  g.insert_directed_edge(0, 2, -35);
  auto pair = g.build(0, 2);
  REQUIRE(pair.first  == -35);
  REQUIRE(pair.second == false);
}

TEST_CASE("Sample Test 2 from ABC137-E.", "[Bellman-Ford]")
{
  auto g = bellman_ford<int>(2);
  g.insert_directed_edge(0, 1, -90);
  g.insert_directed_edge(1, 1, -90);
  auto pair = g.build(0, 1);
  REQUIRE(pair.first  == -std::numeric_limits<int>::max());
  REQUIRE(pair.second == true);
}

TEST_CASE("Sample Test 3 from ABC137-E.", "[Bellman-Ford]")
{
  auto g = bellman_ford<int>(4);
  g.insert_directed_edge(0, 1, 9);
  g.insert_directed_edge(0, 3, 9);
  g.insert_directed_edge(2, 3, 9);
  g.insert_directed_edge(1, 1, -99);
  g.insert_directed_edge(2, 2, -99);
  auto pair = g.build(0, 3);
  REQUIRE(pair.first  == 9);
  REQUIRE(pair.second == false);
}

TEST_CASE("Infinitely near test.", "[Bellman-Ford]")
{
  auto g = bellman_ford<int>(4);
  g.insert_directed_edge(0, 1, -1);
  g.insert_directed_edge(1, 2, -1);
  g.insert_directed_edge(2, 1, -1);
  g.insert_directed_edge(2, 3, -1);
  g.insert_directed_edge(0, 3, -100000);
  auto pair = g.build(0, 3);
  REQUIRE(pair.first  == -std::numeric_limits<int>::max());
  REQUIRE(pair.second == true);
}
