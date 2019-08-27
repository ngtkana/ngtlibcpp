#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <network_flow/dinic.hpp>

struct dinic_tag{};

template <typename DispatchTag>
struct maximum_flow_engine{};

template <>
struct maximum_flow_engine<dinic_tag>{
  dinic<int> storage;
  maximum_flow_engine(int n, int s, int t): storage(n, s, t){}
  void insert(int from, int to, int cap) {storage.insert(from, to, cap);}
  auto build() {return storage.build();}
};

TEMPLATE_TEST_CASE("Maximum Flow Problems", "[dinic]",
  dinic_tag
)
{
  SECTION("AOJ Sample")
  {
    auto max_flow = maximum_flow_engine<TestType>(4, 0, 3);
    max_flow.insert(0, 1, 2);
    max_flow.insert(0, 2, 1);
    max_flow.insert(1, 2, 1);
    max_flow.insert(1, 3, 1);
    max_flow.insert(2, 3, 2);
    REQUIRE(max_flow.build() == 3);
  }
  SECTION("Kyushu Univ. H - Ofuro ha kimochi ii")
  {
    constexpr int inf = 1 << 30;
    auto max_flow = maximum_flow_engine<TestType>(6, 5, 0);
    max_flow.insert(5, 3, inf);
    max_flow.insert(5, 4, inf);
    max_flow.insert(3, 2, 100);
    max_flow.insert(4, 2, 100);
    max_flow.insert(2, 1, 50);
    max_flow.insert(1, 0, 200);
    REQUIRE(max_flow.build() == 50);
  }
}
