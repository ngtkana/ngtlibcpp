// #include <catch2/catch.hpp>
// #include <bits/stdc++.h>
// #include <string_algorighms/suffix_array.hpp>
// #include <string_algorighms/lcp_array.hpp>
// #include "../utility.hpp"
// #define rep(i, begin, end) for(int i = int(begin); i < int(end); i++)
// #define loop(n) for (int ngtkana_is_genius = 0; ngtkana_is_genius < int(n); ngtkana_is_genius++)
// #define rand(l, r) std::uniform_int_distribution<>(l, r)(mt)

// void test(std::string const & s) {
//   int n = s.length();
//   auto const suf = suffix_array(s);
//   auto const lcp = lcp_array(s);
//   rep(i, 0, n - 1) {
//     auto x = suf.at(i), y = suf.at(i + 1);
//     REQUIRE( s.substr(x) < s.substr(y) );
//     auto z = lcp.at(i);
//     REQUIRE( s.substr(x, z) == s.substr(y, z) );
//     REQUIRE( (x + z == n || s.at(x + z) < s.at(y + z)) );
//   }
// }

// TEST_CASE( "Suffix Array Construction Test" "[Suffix Array]" ) {
//   SECTION( "abracadabra" ) {
//     auto suf = suffix_array( "abracadabra" );
//     REQUIRE(suf == std::vector<int>{ 10, 7, 0, 3, 5, 8, 1, 4, 6, 9, 2 });
//   }
//   SECTION( "banana" ) {
//     auto suf = suffix_array( "banana" );
//     REQUIRE(suf == std::vector<int>{ 5, 3, 1, 0, 4, 2 });
//   }
//   SECTION( "nagatakana" ) {
//     auto suf = suffix_array( "nagatakana" );
//     REQUIRE(suf == std::vector<int>{ 9, 1, 5, 7, 3, 2, 6, 8, 0, 4 });
//   }
//   SECTION( "Random Test" ) {
//     loop(24) {
//       std::mt19937 mt(std::random_device{}());
//       auto n = rand(1, 40);
//       std::string s;
//       loop(n) s.push_back('a' + rand(0, 1));
//       test(s);
//     }
//   }
// }
