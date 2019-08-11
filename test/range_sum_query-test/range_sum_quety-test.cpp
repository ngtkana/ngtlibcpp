#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <range_queries/binary_indexed_tree.hpp>
#include <range_queries/segment_tree.hpp>

struct binary_indexed_tree_tag{};
struct segment_tree_tag{};

template <typename T>
class range_sum_query_engine{};

template <>
class range_sum_query_engine<binary_indexed_tree_tag>
{
public:
  static auto new_(int n)
  {
    return make_binary_indexed_tree<int>
    (
      n,
      [](int x, int y){return x + y;},
      [](int x, int y){return x - y;},
      0
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

template <>
class range_sum_query_engine<segment_tree_tag>
{
public:
  static auto new_(int n)
  {
    return make_segment_tree<int>
    (
      n,
      [](int x, int y){return x + y;},
      0
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
  "Range Sum Query Test from the Sample Input 1 of AOJ DSL_2_B",
  "[Binary Indexed Tree,Segment Tree]",
  segment_tree_tag,
  binary_indexed_tree_tag
)
{
  using engine = range_sum_query_engine<TestType>;
  auto instance = engine::new_(3);
  engine::update(instance, 0, 1);
  engine::update(instance, 1, 2);
  engine::update(instance, 2, 3);
  REQUIRE(engine::query(instance, 0, 2) == 3);
  REQUIRE(engine::query(instance, 1, 2) == 2);
}

