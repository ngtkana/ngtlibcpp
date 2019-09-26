#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <range_queries/segment_tree.hpp>
#include <tree/heavy_light_decomposition.hpp>

struct heavy_light_decomposition_tag{};

template <typename DispatchTag>
struct skipping_path_sum_query_engine{};

template <>
class skipping_path_sum_query_engine<heavy_light_decomposition_tag>
{
private:
  segment_tree<int, std::plus<int>> sum_tree;
  heavy_light_decomposition         hld;

public:
  skipping_path_sum_query_engine(int n):
    sum_tree(n, std::plus<int>{}, 0),
    hld(n)
    {}

  void insert (int x, int y)  {hld.insert(x, y);}

  void build ()               {hld.build();}

  void add(int u, int val) {sum_tree.add(hld.id(u), val);}

  int query (int u, int v)
  {
    int ret = 0;
    hld.for_each(u, v, [&](auto l, auto r)
    {
      ret += sum_tree.query(l, r);
    }, true);
    return ret;
  }
};

TEMPLATE_TEST_CASE
(
  "Range Sum Query Test from AOJ GRL_5_D Sample 1",
  "[Heavy-Light Decomposition]",
  heavy_light_decomposition_tag
)
{
  auto engine  = skipping_path_sum_query_engine<TestType>(6);
  engine.insert(0, 1);
  engine.insert(0, 2);
  engine.insert(1, 3);
  engine.insert(1, 5);
  engine.insert(5, 4);
  engine.build();
  REQUIRE(engine.query(0, 1) == 0);
  engine.add(3, 10);
  REQUIRE(engine.query(0, 2) == 0);
  engine.add(4, 20);
  REQUIRE(engine.query(0, 3) == 10);
  engine.add(5, 40);
  REQUIRE(engine.query(0, 4) == 60);
}

TEMPLATE_TEST_CASE
(
  "Range Sum Query Test from AOJ GRL_5_D Sample 2",
  "[Heavy-Light Decomposition]",
  heavy_light_decomposition_tag
)
{
  auto engine  = skipping_path_sum_query_engine<TestType>(4);
  engine.insert(0, 1);
  engine.insert(1, 2);
  engine.insert(2, 3);
  engine.build();
  engine.add(3, 1000);
  engine.add(2, 1000);
  engine.add(1, 1000);
  REQUIRE(engine.query(0, 1) == 1000);
  REQUIRE(engine.query(0, 2) == 2000);
  REQUIRE(engine.query(0, 3) == 3000);
}

TEMPLATE_TEST_CASE
(
  "Range Sum Query Test from AOJ GRL_5_D Sample 3",
  "[Heavy-Light Decomposition]",
  heavy_light_decomposition_tag
)
{
  auto engine  = skipping_path_sum_query_engine<TestType>(2);
  engine.insert(0, 1);
  engine.build();
  engine.add(1, 1);
  REQUIRE(engine.query(0, 1) == 1);
  engine.add(1, 1);
  REQUIRE(engine.query(0, 1) == 2);
}

