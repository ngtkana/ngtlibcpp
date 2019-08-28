#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <network_flow/minimum_cost_flow.hpp>

struct minimum_cost_flow_tag{};

template <typename DispatchTag>
struct minimum_cost_flow_engine{};

template <>
struct minimum_cost_flow_engine<minimum_cost_flow_tag>{
  minimum_cost_flow<int, int> storage;
  minimum_cost_flow_engine(int n, int source, int sink): storage(n, source, sink){}
  void insert (int u, int v, int cap, int cost) { storage.insert(u, v, cap, cost); }
  auto build (int f) { return storage.build(f); }
};

TEMPLATE_TEST_CASE( "Minimum Cost Flow Test", "[minimum_cost_flow]",
  minimum_cost_flow_tag)
{
  SECTION( "AOJ GRL_6_B Sample Input")
  {
    auto engine = minimum_cost_flow_engine<TestType>(4, 0, 3);
    engine.insert(0, 1, 2, 1);
    engine.insert(0, 2, 1, 2);
    engine.insert(1, 2, 1, 1);
    engine.insert(1, 3, 1, 3);
    engine.insert(2, 3, 2, 1);
    REQUIRE(engine.build(2) == 6);
  }
}