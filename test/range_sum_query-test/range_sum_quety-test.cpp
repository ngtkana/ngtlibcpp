#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <range_queries/binary_indexed_tree.hpp>
#include <range_queries/segment_tree.hpp>

struct binary_indexed_tree_tag{};
struct segment_tree_tag{};

template <typename DispatchTag>
class range_sum_query_engine{};

template <>
class range_sum_query_engine<binary_indexed_tree_tag>
{
  using position_type       = int;
  using size_type           = int;
  using add_function_type   = std::plus<int>;
  using sub_function_type   = std::minus<int>;
  using storage_type        = binary_indexed_tree<
                                int,
                                add_function_type,
                                sub_function_type
                              >;
  storage_type storage;

public:
  range_sum_query_engine(int n):
    storage(
      n,
      add_function_type{},
      sub_function_type{},
      0
    )
    {}

  int query(int l, int r) const {return storage.query(l, r);}

  void update(int i, int x) {storage.update(i, x);}
};

template <>
class range_sum_query_engine<segment_tree_tag>
{
  using position_type       = int;
  using size_type           = int;
  using add_function_type   = std::plus<int>;
  using storage_type        = segment_tree<
                                int,
                                add_function_type
                              >;
  storage_type storage;
  static constexpr auto id = 0;

public:
  range_sum_query_engine(int n):
    storage(
      n,
      add_function_type{},
      id
    )
    {}

  int query(int l, int r) const {return storage.query(l, r);}

  void update(int i, int x) {storage.update(i, x);}
};


TEMPLATE_TEST_CASE
(
  "Range Sum Query Test from the Sample Input 1 of AOJ DSL_2_B",
  "[Binary Indexed Tree,Segment Tree]",
  segment_tree_tag,
  binary_indexed_tree_tag
)
{
  auto engine = range_sum_query_engine<TestType>(3);
  engine.update(0, 1);
  engine.update(1, 2);
  engine.update(2, 3);
  REQUIRE(engine.query(0, 2) == 3);
  REQUIRE(engine.query(1, 2) == 2);
}

