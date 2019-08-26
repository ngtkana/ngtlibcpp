#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <disjoint_sets/quick_find.hpp>
#include <disjoint_sets/union_find_tree.hpp>
#include <disjoint_sets/valued_quick_find.hpp>
#include <disjoint_sets/valued_union_find_tree.hpp>
#include <disjoint_sets/weighted_quick_find.hpp>
#include <disjoint_sets/weighted_union_find_tree.hpp>

struct quick_find_tag{};
struct union_find_tree_tag{};
struct valued_quick_find_tag{};
struct valued_union_find_tree_tag{};
struct weighted_quick_find_tag{};
struct weighted_union_find_tree_tag{};

template <typename DispatchTag>
struct disjoint_set_query_engine{};

template <>
struct disjoint_set_query_engine<quick_find_tag>
{
  quick_find storage;
  disjoint_set_query_engine(int n): storage(n) {}
  int find(int x) {return storage.find(x);}
  bool same(int x, int y) {return storage.same(x, y);}
  void unite(int x, int y) {storage.unite(x, y);}
};

template <>
struct disjoint_set_query_engine<union_find_tree_tag>
{
  union_find_tree storage;
  disjoint_set_query_engine(int n): storage(n) {}
  int find(int x) {return storage.find(x);}
  bool same(int x, int y) {return storage.same(x, y);}
  void unite(int x, int y) {storage.unite(x, y);}
};

template <>
struct disjoint_set_query_engine<valued_union_find_tree_tag>
{
  valued_union_find_tree<int, std::plus<int>> storage;
  disjoint_set_query_engine(int n):
    storage(n, std::plus<int>{}, 1, 0) {}
  int find(int x) {return storage.find(x);}
  bool same(int x, int y) {return storage.same(x, y);}
  void unite(int x, int y) {storage.unite(x, y);}
};

template <>
struct disjoint_set_query_engine<weighted_quick_find_tag>
{
  weighted_quick_find<int, std::plus<int>, std::minus<int>> storage;
  disjoint_set_query_engine(int n):
    storage(n, std::plus<int>{}, std::minus<int>{}, 0) {}
  int find(int x) {return storage.find(x);}
  bool same(int x, int y) {return storage.same(x, y);}
  void unite(int x, int y) {storage.unite(x, y, 0);}
};

template <>
struct disjoint_set_query_engine<weighted_union_find_tree_tag>
{
  weighted_union_find_tree<int, std::plus<int>, std::minus<int>> storage;
  disjoint_set_query_engine(int n):
    storage(n, std::plus<int>{}, std::minus<int>{}, 0){}
  int find(int x) {return storage.find(x);}
  bool same(int x, int y) {return storage.same(x, y);}
  void unite(int x, int y) {storage.unite(x, y, 0);}
};

TEMPLATE_TEST_CASE
(
  "Disjoint Sets Test from the Sample Input of AOJ DSL_1_A",
  "[Union-Find Tree, Valued Union-Find Tree, "
  "Weighted Union-Find Tree, Quick Find]",
  quick_find_tag,
  union_find_tree_tag,
  weighted_union_find_tree_tag
)
{
  auto engine = disjoint_set_query_engine<TestType>(5);

  engine.unite(1, 4);
  engine.unite(2, 3);
  REQUIRE(!engine.same(1, 2));
  REQUIRE(!engine.same(3, 4));
  REQUIRE( engine.same(1, 4));
  REQUIRE( engine.same(3, 2));
  engine.unite(1, 3);
  REQUIRE( engine.same(2, 4));
  REQUIRE(!engine.same(3, 0));
  engine.unite(0, 4);
  REQUIRE( engine.same(0, 2));
  REQUIRE( engine.same(3, 0));
}

template <typename DispatchTag>
struct valued_disjoint_set_query_engine{};

template <>
struct valued_disjoint_set_query_engine<valued_union_find_tree_tag>{
  using Op = std::function<int(int, int)>;
  valued_union_find_tree<int, Op> storage;
  valued_disjoint_set_query_engine(int n, const Op& op, int id, int init):
    storage(n, op, id, init){}
  bool unite(int x, int y) {return storage.unite(x, y);}
  void add(int x, int val) {return storage.add(x, val);}
  auto collect_vals()      {return storage.collect_vals();}
};

template <>
struct valued_disjoint_set_query_engine<valued_quick_find_tag>{
  using Op = std::function<int(int, int)>;
  valued_quick_find<int, Op> storage;
  valued_disjoint_set_query_engine(int n, const Op& op, int id, int init):
    storage(n, op, id, init){}
  bool unite(int x, int y) {return storage.unite(x, y);}
  void add(int x, int val) {return storage.add(x, val);}
  auto collect_vals()      {return storage.collect_vals();}
};

#define DISJOINT_SET_TEST_COLLECT_VALS_TEST(...)\
  REQUIRE(uf.collect_vals() == std::vector<int>{__VA_ARGS__});

template <typename T>
std::istream& operator>> (std::istream& is, std::vector<T>& v)
{
  for (auto & x : v) is >> x;
  return is;
}

template <typename T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& v)
{
  auto n = v.size();
  os << "{";
  for (size_t i = 0; i < n; i++)
    os << (i > 0 ? "," : "") << v[i];
  return os << "}";
}

TEMPLATE_TEST_CASE
(
  "Valued Disjoint Sets Tests",
  "[Valued Union-Find Tree, Valued Quick Find]",
  valued_union_find_tree_tag,
  valued_quick_find_tag
)
{
  SECTION("Fron JSC 2019 Qual E - Card Collector (flag method)")
  {
    auto uf = valued_disjoint_set_query_engine<TestType>
    (
      4,
      [](auto x, auto y){return x || y;},
      false,
      false
    );
    REQUIRE(uf.unite(0, 3));
    DISJOINT_SET_TEST_COLLECT_VALS_TEST(false, false, false, false)
    REQUIRE(uf.unite(0, 2));
    DISJOINT_SET_TEST_COLLECT_VALS_TEST(false, false, false, false)
    REQUIRE(!uf.unite(0, 2));
    uf.add(0, 1);
    DISJOINT_SET_TEST_COLLECT_VALS_TEST(true, false, true, true)
    REQUIRE(uf.unite(1, 2));
    DISJOINT_SET_TEST_COLLECT_VALS_TEST(true, true, true, true)
  }

  SECTION("From 2019 Qual E - Card Collector (edge method)")
  {
    auto uf = valued_disjoint_set_query_engine<TestType>
    (
      4,
      [](auto x, auto y){return x + y + 1;},
      0,
      0
    );
    REQUIRE(uf.unite(0, 3));
    DISJOINT_SET_TEST_COLLECT_VALS_TEST(1, 0, 0, 1)
    REQUIRE(uf.unite(0, 2));
    DISJOINT_SET_TEST_COLLECT_VALS_TEST(2, 0, 2, 2)
    REQUIRE(!uf.unite(0, 2));
    uf.add(0, 1);
    DISJOINT_SET_TEST_COLLECT_VALS_TEST(3, 0, 3, 3)
    REQUIRE(uf.unite(1, 2));
    DISJOINT_SET_TEST_COLLECT_VALS_TEST(4, 4, 4, 4);
  }

  SECTION("From JSC 2019 Qual E - Card Collector (edge-plus-one method)")
  {
    auto uf = valued_disjoint_set_query_engine<TestType>
    (
      4,
      [](auto x, auto y){return x + y;},
      0,
      1
    );
    REQUIRE(uf.unite(0, 3));
    DISJOINT_SET_TEST_COLLECT_VALS_TEST(2, 1, 1, 2)
    REQUIRE(uf.unite(0, 2));
    DISJOINT_SET_TEST_COLLECT_VALS_TEST(3, 1, 3, 3)
    REQUIRE(!uf.unite(0, 2));
    uf.add(0, 1);
    DISJOINT_SET_TEST_COLLECT_VALS_TEST(4, 1, 4, 4)
    REQUIRE(uf.unite(1, 2));
    DISJOINT_SET_TEST_COLLECT_VALS_TEST(5, 5, 5, 5)
  }
}



template <typename DispatchTag> struct weighted_disjoint_set_query_engine{};

template <>
struct weighted_disjoint_set_query_engine<weighted_quick_find_tag>{
  weighted_quick_find<int, std::plus<int>, std::minus<int>> storage;
  weighted_disjoint_set_query_engine(int n): storage(n, {}, {}, 0){}
  bool unite(int x, int y, int d) {return storage.unite(x, y, d);}
  auto diff (int x, int y)        {return storage.diff(x, y);}
};

template <>
struct weighted_disjoint_set_query_engine<weighted_union_find_tree_tag>{
  weighted_union_find_tree<int, std::plus<int>, std::minus<int>> storage;
  weighted_disjoint_set_query_engine(int n): storage(n, {}, {}, 0){}
  bool unite(int x, int y, int d) {return storage.unite(x, y, d);}
  auto diff (int x, int y)        {return storage.diff(x, y);}
};

TEMPLATE_TEST_CASE
(
  "Valued Disjoint Sets Test from AOJ DSL_1_B",
  "[Weighted Union-Find Tree, Weighted Quick Find]",
  weighted_quick_find_tag,
  weighted_union_find_tree_tag
)
{
  auto uf = weighted_disjoint_set_query_engine<TestType>(5);
  REQUIRE(uf.unite(2, 0, 5));
  REQUIRE(uf.diff(2, 0) == 5);
  REQUIRE(uf.diff(0, 2) == -5);

  REQUIRE(uf.unite(2, 1, 3));
  REQUIRE(uf.diff(2, 1) == 3);
  REQUIRE(uf.diff(2, 0) == 5);
  REQUIRE(uf.diff(1, 0) == 2);

  REQUIRE(uf.unite(4, 1, 8));
  REQUIRE(uf.diff(4, 1) == 8);
  REQUIRE(uf.diff(4, 2) == 5);
  REQUIRE(uf.diff(4, 0) == 10);
}