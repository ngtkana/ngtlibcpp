#include <catch2/catch.hpp>
#include <bstree.hpp>
#include <bits/stdc++.h>
#include <boost/format.hpp>
#include <boost/hana/repeat.hpp>
#include <boost/hana/type.hpp>
#define loop(n) for (int ngtkana_is_a_genius = 0; ngtkana_is_a_genius < int(n); ngtkana_is_a_genius++)
#define rep(i, begin, end) for (int i = int(begin); (i) < int(end); i++)
#define all(v) v.begin(), v.end()
#define rand(l, r) std::uniform_int_distribution<>(l, r)(mt)
using lint = long long;
auto mt = std::mt19937_64(std::random_device{}());
auto cmn = [](auto& a, auto b){ if (a > b) {a = b; return true;} return false; };
auto cmx = [](auto& a, auto b){ if (a < b) {a = b; return true;} return false; };
void debug_impl() { std::cerr << std::endl; }
template <typename Head, typename... Tail>
void debug_impl(Head head, Tail... tail) { std::cerr << " " << head; debug_impl(tail...); }
#ifndef STOPIT
#define debug(...)\
  do {\
    std::cerr << std::boolalpha << "[" << #__VA_ARGS__ << "]:";\
    debug_impl(__VA_ARGS__);\
    std::cerr << std::noboolalpha;\
  } while (false)
#else
#define debug(...) 0;
#endif

template < typename Container, typename Value = typename Container::value_type, std::enable_if_t<!std::is_same< Container, std::string >::value, std::nullptr_t> = nullptr>
std::istream& operator>> (std::istream& is, Container& v)
  { for (auto & x : v) { is >> x; } return is; }

template < typename Container, typename Value = typename Container::value_type, std::enable_if_t<!std::is_same< Container, std::string >::value, std::nullptr_t> = nullptr >
std::ostream& operator<< (std::ostream& os, Container const& v) {
 os << "{";
  for (auto it = v.begin(); it != v.end(); it++)
    {os << (it != v.begin() ? "," : "") << *it;}
  return os << "}";
}


TEST_CASE( "unit test for nodes" ) {
  using value_type = std::int32_t;
  using node_base_type = bstree_node_base;
  using shared_node_base_type = std::shared_ptr< node_base_type >;
  using node_type = bstree_node< value_type >;
  auto node0 = std::make_shared< node_type >(20);
  auto node1 = std::make_shared< node_type >(10);
  auto node2 = std::make_shared< node_type >(30);
  node0->child[0] = node1;
  node0->child[1] = node2;
  node1->parent = node0;
  node2->parent = node0;
  REQUIRE(shared_node_base_type(node0->child[0]) == node1);
  REQUIRE(shared_node_base_type(node0->child[1]) == node2);
  REQUIRE(shared_node_base_type(node1->parent) == node0);
  REQUIRE(shared_node_base_type(node2->parent) == node0);
  REQUIRE(std::static_pointer_cast< node_type >(node0)->value == 20);
  REQUIRE(std::static_pointer_cast< node_type >(node1)->value == 10);
  REQUIRE(std::static_pointer_cast< node_type >(node2)->value == 30);
}

TEST_CASE( "emulation" ) {
  using value_type = std::int32_t;
  using node_type = bstree_node< value_type >;

  auto force_insert = [&] (std::shared_ptr< node_type > parent, std::size_t pos, value_type value) {
    auto node = std::make_shared< node_type >(value);
    parent->child[pos] = node;
    node->parent = parent;
    return node;
  };

  auto lower_bound = [&] (auto&& root, value_type value) -> std::shared_ptr< node_type > {
    bool upward = false;
    auto now = root;
    while (true) {
      if (upward) {
        auto p = std::static_pointer_cast< node_type >(now->parent.lock());
        if (!p) return {};
        if (value <= p->value) return p;
        now = p;
      } else {
        if (now->value < value) {
          auto r = std::static_pointer_cast< node_type >(now->child[1].lock());
          if (!r) {
            upward = true;
            continue;
          }
          now = r;
        } else {
          auto l = std::static_pointer_cast< node_type >(now->child[0].lock());
          if (!l) return now;
          now = l;
        }
      }
    }
  };

  auto lb_test = [&] (auto&& root, std::int32_t key, std::int32_t expected) {
    REQUIRE(lower_bound(root, key)->value == expected);
  };

  auto insert = [&] (auto&& storage, auto&& root, value_type value) -> std::shared_ptr< node_type > {
    auto set_child = [&] (auto&& parent, value_type value, std::size_t pos) {
      auto child = std::make_shared< node_type >(value);
      storage.emplace_back(child);
      parent->child[pos] = child;
      child->parent = parent;
      return child;
    };
    auto lb = lower_bound(root, value);
    if (!lb) {
      auto now = root;
      while (true) {
        auto r = std::static_pointer_cast< node_type >(now->child[1].lock());
        if (!r) {
          return set_child(now, value, 1);
        }
        now = r;
      }
    } else {
      auto now = lb;
      auto l = std::static_pointer_cast< node_type >(now->child[0].lock());
      if (!l) {
        return set_child(now, value, 0);
      } else {
        now = l;
        while (true) {
          auto r = std::static_pointer_cast< node_type >(now->child[1].lock());
          if (!r) {
            return set_child(now, value, 1);
          }
          now = r;
        }
      }
    }
  };

  SECTION( "find" ) {
    SECTION( "typical" ) {
      auto root = std::make_shared< node_type >(10);
      auto node5 = force_insert(root, 0, 5);
      auto node15 = force_insert(root, 1, 15);
      auto node2 = force_insert(node5, 0, 2);
      auto node7 = force_insert(node5, 1, 7);
      auto node12 = force_insert(node15, 0, 12);
      lb_test(root, 0, 2);
      lb_test(root, 1, 2);
      lb_test(root, 2, 2);
      lb_test(root, 3, 5);
      lb_test(root, 4, 5);
      lb_test(root, 5, 5);
      lb_test(root, 6, 7);
      lb_test(root, 7, 7);
      lb_test(root, 8, 10);
      lb_test(root, 9, 10);
      lb_test(root, 10, 10);
      lb_test(root, 11, 12);
      lb_test(root, 12, 12);
      lb_test(root, 13, 15);
      lb_test(root, 14, 15);
      lb_test(root, 15, 15);
      REQUIRE_FALSE(lower_bound(root, 16));
      REQUIRE_FALSE(lower_bound(root, 17));
      REQUIRE_FALSE(lower_bound(root, 18));
    }
    SECTION( "singleton" ) {
      auto root = std::make_shared< node_type >(10);
      lb_test(root, 8, 10);
      lb_test(root, 9, 10);
      lb_test(root, 10, 10);
      REQUIRE_FALSE(lower_bound(root, 11));
      REQUIRE_FALSE(lower_bound(root, 12));
      REQUIRE_FALSE(lower_bound(root, 13));
    }
  }

  SECTION( "insert any order" ) {
    std::vector< std::shared_ptr< node_type > > storage;
    std::vector< value_type > values{ 2, 5, 7, 10, 12 };

    boost::hana::repeat(boost::hana::int_c< 120 >, [&]{
      auto root = std::make_shared< node_type >(values.front());
      for (auto value : values) {
        if (value == values.front()) continue;
        insert(storage, root, value);
      }
      lb_test(root, 0, 2);
      lb_test(root, 1, 2);
      lb_test(root, 2, 2);
      lb_test(root, 3, 5);
      lb_test(root, 4, 5);
      lb_test(root, 5, 5);
      lb_test(root, 6, 7);
      lb_test(root, 7, 7);
      lb_test(root, 8, 10);
      lb_test(root, 9, 10);
      lb_test(root, 10, 10);
      lb_test(root, 11, 12);
      lb_test(root, 12, 12);
      REQUIRE_FALSE(lower_bound(root, 13));
      REQUIRE_FALSE(lower_bound(root, 14));
      REQUIRE_FALSE(lower_bound(root, 15));
      std::next_permutation(all(values));
    });
  }
}