#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <disjoint_sets/quick_find.hpp>
#include <disjoint_sets/union_find_tree.hpp>
#include <disjoint_sets/weighted_union_find_tree.hpp>

struct quick_find_tag{};
struct union_find_tree_tag{};
struct weighted_union_find_tree_tag{};

template <typename DispatchTag>
class disjoint_set_query_engine{};

template <>
class disjoint_set_query_engine<quick_find_tag>
{
  using node_type    = int;
  using size_type    = int;
  using storage_type = quick_find;

  storage_type storage;

public:
  disjoint_set_query_engine(int n): storage(n) {}

  node_type find(node_type x) {return storage.find(x);}

  bool is_equiv(node_type x, node_type y) {return storage.is_equiv(x, y);}

  void unite(node_type x, node_type y) {storage.unite(x, y);}
};

template <>
class disjoint_set_query_engine<union_find_tree_tag>
{
  using node_type    = int;
  using size_type    = int;
  using storage_type = union_find_tree;

  storage_type storage;

public:
  disjoint_set_query_engine(int n): storage(n) {}

  node_type find(node_type x) {return storage.find(x);}

  bool is_equiv(node_type x, node_type y) {return storage.is_equiv(x, y);}

  void unite(node_type x, node_type y) {storage.unite(x, y);}
};

template <>
class disjoint_set_query_engine<weighted_union_find_tree_tag>
{
  using node_type    = int;
  using size_type    = int;
  using storage_type = weighted_union_find_tree<int>;

  storage_type storage;

public:
  disjoint_set_query_engine(int n): storage(n) {}

  node_type find(node_type x) {return storage.find(x);}

  bool is_equiv(node_type x, node_type y) {return storage.is_equiv(x, y);}

  void unite(node_type x, node_type y) {storage.unite(x, y, 0);}
};


TEMPLATE_TEST_CASE
(
  "Disjoint Sets Test from the Sample Input of AOJ DSL_1_A",
  "[Union-find Tree, Weighted Union-find Tree, Quick Find]",
  quick_find_tag,
  union_find_tree_tag,
  weighted_union_find_tree_tag
)
{
  auto engine = disjoint_set_query_engine<TestType>(5);

  engine.unite(1, 4);
  engine.unite(2, 3);
  REQUIRE(!engine.is_equiv(1, 2));
  REQUIRE(!engine.is_equiv(3, 4));
  REQUIRE( engine.is_equiv(1, 4));
  REQUIRE( engine.is_equiv(3, 2));
  engine.unite(1, 3);
  REQUIRE( engine.is_equiv(2, 4));
  REQUIRE(!engine.is_equiv(3, 0));
  engine.unite(0, 4);
  REQUIRE( engine.is_equiv(0, 2));
  REQUIRE( engine.is_equiv(3, 0));
}