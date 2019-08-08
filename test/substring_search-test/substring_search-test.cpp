#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <string_algorighms/kmp_algorithm.hpp>
#include <string_algorighms/z_algorithm.hpp>

struct kmp_algorithm_tag{};
struct z_algorithm_tag{};

auto substring_search(std::string w, std::string s, kmp_algorithm_tag) {
  return kmp_search(w, s);
}
auto substring_search(std::string w, std::string s, z_algorithm_tag) {
  return z_search(w, s);
}

#define SUBSTRING_SEARCH_TEST(w_rv, s_rv, v_rv)\
  REQUIRE(substring_search(w_rv, s_rv, TestType{}) == v_rv);

TEMPLATE_TEST_CASE(
    "Substring Search Test",
    "[KMP Algorithm, Z Algorithm]",
    kmp_algorithm_tag,
    z_algorithm_tag
  )
  {
    SUBSTRING_SEARCH_TEST(
      "abc",
      "xabcabzabc",
      (std::vector<int>{1, 7})
    );
    SUBSTRING_SEARCH_TEST(
      "ABCDABD",
      "ABCXABCDABXABCDABCDABDE",
      (std::vector<int>{15})
    );
    SUBSTRING_SEARCH_TEST(
      "ABC",
      "ABACABABC",
      (std::vector<int>{6})
    );
    SUBSTRING_SEARCH_TEST(
      "bra",
      "abracadabra",
      (std::vector<int>{1, 8})
    );
  }
