#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <dinic.hpp>

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
  SECTION(u8"AOJ Sample")
  {
    auto max_flow = maximum_flow_engine<TestType>(4, 0, 3);
    max_flow.insert(0, 1, 2);
    max_flow.insert(0, 2, 1);
    max_flow.insert(1, 2, 1);
    max_flow.insert(1, 3, 1);
    max_flow.insert(2, 3, 2);
    REQUIRE(max_flow.build() == 3);
  }

  SECTION(u8"Kyushu Univ. H - お風呂は気持ちいい")
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

  SECTION(u8"yukicoder 117 制作進行の宮森あおいです！")
  {
    constexpr int inf = 1 << 30;
    auto max_flow = maximum_flow_engine<TestType>(14, 12, 13);
    for (auto i = 0; i < 10; i++)
    {
      auto cap = (i + 1) * 2;
      max_flow.insert(12, i, cap);
      max_flow.insert(i, (i < 5 ? 10 : 11), inf);
    }
    max_flow.insert(10, 13, 50);
    max_flow.insert(11, 13, 70);
    REQUIRE(max_flow.build() == 100);
  }

  SECTION(u8"yukicoder No.654 Air E869120")
  {
    constexpr int linf = 1 << 30;
    auto max_flow = maximum_flow_engine<TestType>(12, 10, 11);
    max_flow.insert(0, 5, 40);
    max_flow.insert(1, 8, 10);
    max_flow.insert(2, 7, 20);
    max_flow.insert(3, 8, 20);
    max_flow.insert(4, 9, 30);
    max_flow.insert(10, 0, linf);
    max_flow.insert(10, 1, linf);
    max_flow.insert(0, 1, linf);
    max_flow.insert(5, 2, linf);
    max_flow.insert(2, 3, linf);
    max_flow.insert(8, 7, linf);
    max_flow.insert(7, 4, linf);
    max_flow.insert(9, 8, linf);
    max_flow.insert(9, 11, linf);
    max_flow.insert(8, 11, linf);
    REQUIRE(max_flow.build() == 50);
  }
}
