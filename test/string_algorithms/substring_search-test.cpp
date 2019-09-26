#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <string_algorighms/kmp_algorithm.hpp>
#include <string_algorighms/z_algorithm.hpp>
#include <string_algorighms/suffix_array.hpp>

struct kmp_algorithm_tag{};
struct z_algorithm_tag{};
struct suffix_array_tag{};

template <typename DispatchTag>
struct substring_search_engine{};

template <>
struct substring_search_engine<kmp_algorithm_tag> {
  substring_search_engine()=default;
  auto search(const std::string& w, const std::string& s) {
    auto kmp = kmp_algorithm(w);
    return kmp.search(s);
  }
};

template <>
struct substring_search_engine<z_algorithm_tag> {
  substring_search_engine()=default;
  auto search(const std::string& w, const std::string& s)
    { return z_search(w, s, '$'); }
};

#define SUBSTRING_SEARCH_TEST(w_rv, s_rv, v_rv) {\
    auto engine = substring_search_engine<TestType>{};\
    REQUIRE(engine.search(w_rv, s_rv) == v_rv);\
  }\

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
