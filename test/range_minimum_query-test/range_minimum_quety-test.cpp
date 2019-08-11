#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <range_queries/binary_indexed_tree.hpp>
#include <range_queries/segment_tree.hpp>
#include "../utility.hpp"

struct segment_tree_tag{};

template <typename DispatchTag>
class range_minimum_query_engine{};

template <>
class range_minimum_query_engine<segment_tree_tag>
{
  using position_type       = int;
  using size_type           = int;
  using merge_function_type = minimum_function_t<int, int>;
  using storage_type        = segment_tree<
                                int,
                                merge_function_type
                              >;
  storage_type storage;
  static constexpr auto id = std::numeric_limits<int>::max();

public:
  range_minimum_query_engine(int n):
    storage(
      n,
      merge_function_type{},
      id
    )
    {}

  int query(int l, int r) const {return storage.query(l, r);}

  void update(int i, int x) {storage.update(i, x);}
};


TEMPLATE_TEST_CASE
(
  "Range minimum Query Test from the Sample Input 1 of AOJ DSL_2_A",
  "[Segment Tree]",
  segment_tree_tag
)
{
  auto engine = range_minimum_query_engine<TestType>(3);
  engine.update(0, 1);
  engine.update(1, 2);
  engine.update(2, 3);
  REQUIRE(engine.query(0, 2) == 1);
  REQUIRE(engine.query(1, 2) == 2);
}

TEMPLATE_TEST_CASE
(
  "Range minimum Query Test from the Sample Input 2 of AOJ DSL_2_A",
  "[Segment Tree]",
  segment_tree_tag
)
{
  auto engine = range_minimum_query_engine<TestType>(1);
  REQUIRE(engine.query(0, 1) == std::numeric_limits<int>::max());
  engine.update(0, 5);
  REQUIRE(engine.query(0, 1) == 5);
}

