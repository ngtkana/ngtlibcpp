#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <range_queries/binary_indexed_tree.hpp>
#include <range_queries/segment_tree.hpp>
#include <range_queries/lazy_segment_tree.hpp>
#include "../utility.hpp"

struct binary_indexed_tree_tag{};
struct segment_tree_tag{};
struct lazy_segment_tree_tag{};

template <typename DispatchTag>
class range_sum_query_engine{};

template <>
class range_sum_query_engine<binary_indexed_tree_tag>
{
  binary_indexed_tree<int, sum_fn_t, dif_fn_t> sum_tree;

public:
  range_sum_query_engine(int n):
    sum_tree(n, sum_fn, dif_fn, 0)
    {}

  int  query (int l, int r) const {return sum_tree.query(l, r);}

  void update(int i, int x)       {sum_tree.update(i, x);}
};

template <>
class range_sum_query_engine<segment_tree_tag>
{
  segment_tree<int, sum_fn_t> sum_tree;

public:
  range_sum_query_engine(int n):
    sum_tree(n, sum_fn, 0)
    {}

  int  query (int l, int r) const {return sum_tree.query(l, r);}

  void update(int i, int x)       {sum_tree.update(i, x);}
};

template <>
class range_sum_query_engine<lazy_segment_tree_tag>
{
  private:
    lazy_segment_tree<int, int,
        sum_fn_t, update_fn_t, update_fn_t,
        twice_fn_t, half_fn_t
      >
      sum_tree;

  public:
    range_sum_query_engine(int n):
      sum_tree(
        n, sum_fn, update_fn, update_fn, 0, -1, twice_fn, half_fn
      )
      {}

    int  query (int l, int r) {return sum_tree.query(l, r);}

    void update(int i, int x) {sum_tree.act(i, i + 1, x);}
};

TEMPLATE_TEST_CASE
(
  "Range Sum Query Test from the Sample Input 1 of AOJ DSL_2_B",
  "[Binary Indexed Tree,Segment Tree]",
  binary_indexed_tree_tag,
  segment_tree_tag,
  lazy_segment_tree_tag
)
{
  auto engine = range_sum_query_engine<TestType>(3);
  engine.update(0, 1);
  engine.update(1, 2);
  engine.update(2, 3);
  REQUIRE(engine.query(0, 2) == 3);
  REQUIRE(engine.query(1, 2) == 2);
}

