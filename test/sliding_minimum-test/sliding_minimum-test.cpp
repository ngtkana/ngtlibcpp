#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <range_queries/segment_tree.hpp>
#include <range_queries/sliding_minimum.hpp>
#include "../utility.hpp"

struct sliding_minimum_tag{};
struct segment_tree_tag{};

template <typename DispatchTag>
class sliding_minimum_query_engine{};

template <>
class sliding_minimum_query_engine<sliding_minimum_tag>
{
  sliding_minimum<int> storage;

public:
  sliding_minimum_query_engine (const std::vector<int>& v)
    : storage(std::move(v))
  {}

  auto query() const {return storage.query();}

  void pop_left()  {storage.pop_left();}

  void push_right() {storage.push_right();}
};

template <>
class sliding_minimum_query_engine<segment_tree_tag>
{
  int                         left, right;
  segment_tree<int, min_fn_t> min_tree;

public:
  sliding_minimum_query_engine(int n):
    left    (0),
    right   (0),
    min_tree(n, min_fn, inf)
    {}

  int  query (int l, int r) const {return min_tree.query(l, r);}

  void update(int i, int x)       {min_tree.update(i, x);}


public:
  sliding_minimum_query_engine (const std::vector<int>& v):
    left (0),
    right(0),
    min_tree(v.size(), min_fn, inf, std::move(v))
    {}

  auto query() const {return min_tree.query(left, right);}

  void pop_left()   {left++;}

  void push_right() {right++;}
};



#define SLIDING_MINIMIM_TEST(x) \
  engine.pop_left();\
  engine.push_right();\
  REQUIRE(engine.query() == x);

TEMPLATE_TEST_CASE
(
  "Range Sum Query Test from the Sample Input 1 of AOJ DSL_3_D",
  "[Binary Indexed Tree,Segment Tree]",
  sliding_minimum_tag
)
{
  auto engine = sliding_minimum_query_engine<TestType>
  (
    {1, 7, 7, 4, 8, 1, 6}
  );
  engine.push_right();
  engine.push_right();
  engine.push_right();
  REQUIRE(engine.query() == 1);
  SLIDING_MINIMIM_TEST(4);
  SLIDING_MINIMIM_TEST(4);
  SLIDING_MINIMIM_TEST(1);
  SLIDING_MINIMIM_TEST(1);
}

