#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <range_queries/binary_indexed_tree.hpp>
#include <range_queries/segment_tree.hpp>

struct segment_tree_tag{};

template <typename T>
class range_minimum_query_engine{};

template <>
class range_minimum_query_engine<segment_tree_tag>
{
public:
  static auto new_(int n)
  {
    return make_segment_tree<int>
    (
      n,
      [](int x, int y){return std::min(x, y);},
      std::numeric_limits<int>::max()
    );
  }

  template <typename Storage>
  static int query(Storage const& storage, int l, int r)
  {
    return storage.query(l, r);
  }

  template <typename Storage>
  static void update(Storage& storage, int i, int x)
  {
    storage.update(i, x);
  }
};


TEMPLATE_TEST_CASE
(
  "Range minimum Query Test from the Sample Input 1 of AOJ DSL_2_A",
  "[Segment Tree]",
  segment_tree_tag
)
{
  using engine = range_minimum_query_engine<TestType>;
  auto instance = engine::new_(3);
  engine::update(instance, 0, 1);
  engine::update(instance, 1, 2);
  engine::update(instance, 2, 3);
  REQUIRE(engine::query(instance, 0, 2) == 1);
  REQUIRE(engine::query(instance, 1, 2) == 2);
}

TEMPLATE_TEST_CASE
(
  "Range minimum Query Test from the Sample Input 2 of AOJ DSL_2_A",
  "[Segment Tree]",
  segment_tree_tag
)
{
  using engine = range_minimum_query_engine<TestType>;
  auto instance = engine::new_(1);
  REQUIRE(engine::query(instance, 0, 1) == std::numeric_limits<int>::max());
  engine::update(instance, 0, 5);
  REQUIRE(engine::query(instance, 0, 1) == 5);
}

