// #include <catch2/catch.hpp>
// #include <bits/stdc++.h>
// #include <utility/fmt.hpp>
// #define loop(n) for (int ngtkana_is_genius = 0; ngtkana_is_genius < int(n); ngtkana_is_genius++)
// #define rep(i, begin, end) for(int i = int(begin); i < int(end); i++)
// #define all(v) v.begin(), v.end()
// #define rand(l, r) std::uniform_int_distribution<>(l, r)(mt)
// using lint = long long;
// auto cmn = [](auto& a, auto b){if (a > b) {a = b; return true;} return false;};
// auto cmx = [](auto& a, auto b){if (a < b) {a = b; return true;} return false;};
// void debug_impl() { std::cerr << std::endl; }
// template <typename Head, typename... Tail>
// void debug_impl(Head head, Tail... tail){
//   std::cerr << " " << head;
//   debug_impl(tail...);
// }
// #ifndef STOPIT
// #define debug(...)\
//   std::cerr << std::boolalpha << "[" << #__VA_ARGS__ << "]:";\
//   debug_impl(__VA_ARGS__);\
//   std::cerr << std::noboolalpha;
// #else
// #define debug 0;
// #endif

// #define FORMAT_TEST(b, c, ...)\
//   do {\
//     SECTION( "rvalue and rvalue" ) {\
//       REQUIRE(fmt(__VA_ARGS__)(b) == c);\
//     }\
//     SECTION( "lvalue and rvalue" ) {\
//       auto const x = fmt(__VA_ARGS__);\
//       REQUIRE(x(b) == c);\
//     }\
//     SECTION( "rvalue and lvalue") {\
//       auto const y = b;\
//       REQUIRE(fmt(__VA_ARGS__)(y) == c);\
//     }\
//     SECTION( "lvalue and lvalue" ) {\
//       auto const x = fmt(__VA_ARGS__);\
//       auto const y = b;\
//       REQUIRE(x(y) == c);\
//     }\
//   } while (false)

// template < class Head, class ... Tails >
// auto make_vector(Head&& head, Tails&& ... tails)
//   { return std::vector< Head >{ head, tails ...}; }

// TEST_CASE( "fmt", "[fmt]" ) {
//   using namespace std::literals::string_literals;
//   SECTION( "one exception and a primitive or string-like types" ) {
//     SECTION( "integral types" ) {
//       SECTION( "int and int" ) {
//         FORMAT_TEST(0, "_"s, 0);
//         FORMAT_TEST(0, "_"s, 0);
//         FORMAT_TEST(1, "1"s, 0);
//         FORMAT_TEST(0, "0"s, 1);
//         FORMAT_TEST(1, "_"s, 1);
//       }
//       SECTION( "int and long long" ) {
//         FORMAT_TEST(0LL, "_"s, 0);
//         FORMAT_TEST(1LL, "1"s, 0);
//         FORMAT_TEST(0LL, "0"s, 1);
//         FORMAT_TEST(1LL, "_"s, 1);
//       }
//       SECTION( "long long and int" ) {
//         FORMAT_TEST(0, "_"s, 0LL);
//         FORMAT_TEST(1, "1"s, 0LL);
//         FORMAT_TEST(0, "0"s, 1LL);
//         FORMAT_TEST(1, "_"s, 1LL);
//       }
//       SECTION( "long long and long long" ) {
//         FORMAT_TEST(0LL, "_"s, 0LL);
//         FORMAT_TEST(1LL, "1"s, 0LL);
//         FORMAT_TEST(0LL, "0"s, 1LL);
//         FORMAT_TEST(1LL, "_"s, 1LL);
//       }
//     }

//     SECTION( "floating-point types" ) {
//       SECTION( "double and double" ) {
//         FORMAT_TEST(0., "_"s, 0.);
//         FORMAT_TEST(1., "1.000000"s, 0.);
//         FORMAT_TEST(0., "0.000000"s, 1.);
//         FORMAT_TEST(1., "_"s, 1.);
//       }
//     }

//     SECTION( "integral and floating-point types" ) {
//       SECTION( "int and double" ) {
//         FORMAT_TEST(0., "_"s, 0);
//         FORMAT_TEST(1., "1.000000"s, 0);
//         FORMAT_TEST(0., "0.000000"s, 1);
//         FORMAT_TEST(1., "_"s, 1);
//       }
//       SECTION( "double and int" ) {
//         FORMAT_TEST(0, "_"s, 0.);
//         FORMAT_TEST(1, "1"s, 0.);
//         FORMAT_TEST(0, "0"s, 1.);
//         FORMAT_TEST(1, "_"s, 1.);
//       }
//     }

//     SECTION( "string-like types" ) {
//       SECTION( "char and char" ) {
//         FORMAT_TEST('a', "_"s, 'a');
//         FORMAT_TEST('b', "\'b\'"s, 'a');
//         FORMAT_TEST('a', "\'a\'"s, 'b');
//         FORMAT_TEST('b', "_"s, 'b');
//       }
//       SECTION( "char and char[]" ) {
//         FORMAT_TEST("a", "\"a\"", 'a');
//         FORMAT_TEST("b", "\"b\"", 'a');
//         FORMAT_TEST("ab", "\"ab\"", 'a');
//       }
//       SECTION( "char and string" ) {
//         FORMAT_TEST("a"s, "\"a\"", 'a');
//         FORMAT_TEST("b"s, "\"b\"", 'a');
//         FORMAT_TEST("ab"s, "\"ab\"", 'a');
//       }
//       SECTION( "char[] and char" ) {
//         FORMAT_TEST('a', "\'a\'", "a");
//         FORMAT_TEST('a', "\'a\'", "b");
//         FORMAT_TEST('a', "\'a\'", "ab");
//       }
//       SECTION( "char[] and char[]" ) {
//         FORMAT_TEST("a", "_", "a");
//         FORMAT_TEST("b", "\"b\"", "a");
//         FORMAT_TEST("ab", "\"ab\"", "a");
//       }
//       SECTION( "char[] and string" ) {
//         FORMAT_TEST("a"s, "_", "a");
//         FORMAT_TEST("b"s, "\"b\"", "a");
//         FORMAT_TEST("ab"s, "\"ab\"", "a");
//       }
//       SECTION( "string and char" ) {
//         FORMAT_TEST('a', "\'a\'", "a"s);
//         FORMAT_TEST('a', "\'a\'", "b"s);
//         FORMAT_TEST('a', "\'a\'", "ab"s);
//       }
//       SECTION( "string and char[]" ) {
//         FORMAT_TEST("a", "_", "a"s);
//         FORMAT_TEST("a", "\"a\"", "b"s);
//         FORMAT_TEST("a", "\"a\"", "ab"s);
//       }
//       SECTION( "string and string" ) {
//         FORMAT_TEST("a"s, "_", "a"s);
//         FORMAT_TEST("a"s, "\"a\"", "b"s);
//         FORMAT_TEST("a"s, "\"a\"", "ab"s);
//       }
//     }

//     SECTION( "char and other integral types" ) {
//       SECTION( "char and int" ) {
//         FORMAT_TEST(97, "97"s, 'a');
//         FORMAT_TEST(98, "98"s, 'a');
//         FORMAT_TEST(97, "97"s, 'b');
//         FORMAT_TEST(98, "98"s, 'b');
//       }
//       SECTION( "char and long long" ) {
//         FORMAT_TEST(97LL, "97"s, 'a');
//         FORMAT_TEST(98LL, "98"s, 'a');
//         FORMAT_TEST(97LL, "97"s, 'b');
//         FORMAT_TEST(98LL, "98"s, 'b');
//       }
//       SECTION( "int and char" ) {
//         FORMAT_TEST('a', "\'a\'"s, 97);
//         FORMAT_TEST('a', "\'a\'"s, 98);
//         FORMAT_TEST('b', "\'b\'"s, 97);
//         FORMAT_TEST('b', "\'b\'"s, 98);
//       }
//       SECTION( "long long and char" ) {
//         FORMAT_TEST('a', "\'a\'"s, 97LL);
//         FORMAT_TEST('a', "\'a\'"s, 98LL);
//         FORMAT_TEST('b', "\'b\'"s, 97LL);
//         FORMAT_TEST('b', "\'b\'"s, 98LL);
//       }
//     }
//   }

//   SECTION( "one exception and a vector" ) {
//     SECTION( "int and a vector" ) {
//       FORMAT_TEST((make_vector(0, 1)), "{_,1}", 0);
//       FORMAT_TEST((make_vector(0LL, 1LL)), "{_,1}", 0);
//       FORMAT_TEST((make_vector('a', 'b')), "{\'a\',\'b\'}", 97);
//       FORMAT_TEST((make_vector("a"s, "b"s)), "{\"a\",\"b\"}", 97);
//     }
//     SECTION( "char and a vector" ) {
//       FORMAT_TEST((make_vector(97, 98)), "{97,98}", 'a');
//       FORMAT_TEST((make_vector(97LL, 98LL)), "{97,98}", 'a');
//       FORMAT_TEST((make_vector('a', 'b')), "{_,\'b\'}", 'a');
//       FORMAT_TEST((make_vector("a"s, "b"s)), "{\"a\",\"b\"}", 'a');
//     }
//     SECTION( "char[] and a vector" ) {
//       FORMAT_TEST((make_vector(97, 98)), "{97,98}", "a");
//       FORMAT_TEST((make_vector(97LL, 98LL)), "{97,98}", "a");
//       FORMAT_TEST((make_vector('a', 'b')), "{\'a\',\'b\'}", "a");
//       FORMAT_TEST((make_vector("a"s, "b"s)), "{_,\"b\"}", "a");
//     }
//     SECTION( "string and a vector" ) {
//       FORMAT_TEST((make_vector(97, 98)), "{97,98}", "a"s);
//       FORMAT_TEST((make_vector(97LL, 98LL)), "{97,98}", "a"s);
//       FORMAT_TEST((make_vector('a', 'b')), "{\'a\',\'b\'}", "a"s);
//       FORMAT_TEST((make_vector("a"s, "b"s)), "{_,\"b\"}", "a"s);
//     }
//   }

//   SECTION( "one exception and a tuple" ) {
//     SECTION( "int and a tuple" ) {
//       FORMAT_TEST(
//         (std::make_tuple(97, 98, 97LL, 98LL, 'a', 'b', "a"s, "b"s)),
//         "(_,98,_,98,\'a\',\'b\',\"a\",\"b\")",
//         97
//         );
//     }
//     SECTION( "long long and a tuple" ) {
//       FORMAT_TEST(
//         (std::make_tuple(97, 98, 97LL, 98LL, 'a', 'b', "a"s, "b"s)),
//         "(_,98,_,98,\'a\',\'b\',\"a\",\"b\")",
//         97LL
//         );
//     }
//     SECTION( "char and a tuple" ) {
//       FORMAT_TEST(
//         (std::make_tuple(97, 98, 97LL, 98LL, 'a', 'b', "a"s, "b"s)),
//         "(97,98,97,98,_,\'b\',\"a\",\"b\")",
//         'a'
//         );
//     }
//     SECTION( "char[] and a tuple" ) {
//       FORMAT_TEST(
//         (std::make_tuple(97, 98, 97LL, 98LL, 'a', 'b', "a"s, "b"s)),
//         "(97,98,97,98,\'a\',\'b\',_,\"b\")",
//         "a"
//         );
//     }
//     SECTION( "string and a tuple" ) {
//       FORMAT_TEST(
//         (std::make_tuple(97, 98, 97LL, 98LL, 'a', 'b', "a"s, "b"s)),
//         "(97,98,97,98,\'a\',\'b\',_,\"b\")",
//         "a"s
//         );
//     }

//   }

//   SECTION( "one exception and a tuple-in-a-vector" ) {
//     SECTION( "int and a tuple-in-a-vector" ) {
//       FORMAT_TEST(
//         (make_vector(std::make_tuple(97, 'a'), std::make_tuple(98, 'b'))),
//         "{(_,\'a\'),(98,\'b\')}",
//         97
//         );
//     }
//     SECTION( "long long and a tuple-in-a-vector" ) {
//       FORMAT_TEST(
//         (make_vector(std::make_tuple(97, 'a'), std::make_tuple(98, 'b'))),
//         "{(_,\'a\'),(98,\'b\')}",
//         97LL
//         );
//     }
//     SECTION( "char and a tuple-in-a-vector" ) {
//       FORMAT_TEST(
//         (make_vector(std::make_tuple(97, 'a'), std::make_tuple(98, 'b'))),
//         "{(97,_),(98,\'b\')}",
//         'a'
//         );
//     }
//     SECTION( "char[] and a tuple-in-a-vector" ) {
//       FORMAT_TEST(
//         (make_vector(std::make_tuple(97, 'a'), std::make_tuple(98, 'b'))),
//         "{(97,\'a\'),(98,\'b\')}",
//         "a"
//         );
//     }
//     SECTION( "string and a tuple-in-a-vector" ) {
//       FORMAT_TEST(
//         (make_vector(std::make_tuple(97, 'a'), std::make_tuple(98, 'b'))),
//         "{(97,\'a\'),(98,\'b\')}",
//         "a"s
//         );
//     }
//   }

//   SECTION( "one exception and a vector-in-a-tuple" ) {
//     FORMAT_TEST(
//       (std::make_tuple(make_vector(97, 98), make_vector('a', 'b'))),
//       "({_,98},{'a','b'})",
//       97
//     );
//     FORMAT_TEST(
//       (std::make_tuple(make_vector(97, 98), make_vector('a', 'b'))),
//       "({97,98},{_,'b'})",
//       'a'
//     );
//   }

//   SECTION( "vector-exception and a vector" ) {
//     SECTION( "type match" ) {
//       FORMAT_TEST((make_vector(97, 98, 99)), "_", (make_vector(97, 98, 99)));
//       FORMAT_TEST((make_vector(97, 98, 99)), "{97,98,99}", (make_vector(96, 98, 99)));
//       FORMAT_TEST((make_vector(97, 98, 99)), "{97,98,99}", (make_vector('a', 'b', 'c'))); // TODO: we want to detect it
//       FORMAT_TEST((make_vector(97, 98, 99)), "{97,98,99}", (make_vector(96, 98, 99)));
//       FORMAT_TEST((make_vector(97, 98, 99)), "_", (make_vector(97, 98, 99)));
//       FORMAT_TEST((make_vector('a', 'b', 'c')), "{'a','b','c'}", (make_vector(96, 98, 99)));
//     }
//     SECTION( "type mismatch" ) {
//       FORMAT_TEST((make_vector(97, 98, 99)), "{97,98,99}", (make_vector('a', 'b', 'c')));
//       FORMAT_TEST((make_vector('a', 'b', 'c')), "{'a','b','c'}", (make_vector(97, 98, 99)));
//     }
//   }

//   SECTION( "tuple-exception and a tuple" ) {
//     SECTION( "type match" ) {
//       FORMAT_TEST((std::make_tuple(97, 'b', "c")), "_", (std::make_tuple(97, 'b', "c")));
//       FORMAT_TEST((std::make_tuple(97, 'b', "c")), "(97,'b',\"c\")", (std::make_tuple(97, 'b', "k")));
//     }
//     SECTION( "type mismatch") {
//       FORMAT_TEST((std::make_tuple(97, 'b', "c")), "_", (std::make_tuple(97LL, 'b', "c"))); // TODO: stop detect this
//       FORMAT_TEST((std::make_tuple(97, 'b', "c")), "_", (std::make_tuple(97, 98, "c"))); // TODO: stop detect this
//     }
//   }

//   SECTION( "subobject-match" ) {
//     SECTION( "vector in a tuple" ) {
//       FORMAT_TEST(
//         (std::make_tuple(make_vector(97, 98), make_vector('a', 'b'))),
//         "(_,{'a','b'})",
//         make_vector(97, 98)
//       );
//       FORMAT_TEST(
//         (std::make_tuple(make_vector(97, 98), make_vector('a', 'b'))),
//         "({97,98},_)",
//         make_vector('a','b')
//       );
//     }
//     SECTION( "tuple in vector" ) {
//       FORMAT_TEST(
//         (make_vector(std::make_tuple(97, 'a'), std::make_tuple(98, 'b'))),
//         "{_,(98,'b')}",
//         std::make_tuple(97, 'a')
//       );
//       FORMAT_TEST(
//         (make_vector(std::make_tuple(97, 'a'), std::make_tuple(98, 'b'))),
//         "{(97,'a'),(98,'b')}",
//         std::make_tuple(97, 98)
//       );
//       FORMAT_TEST(
//         (make_vector(std::make_tuple(97, 'a'), std::make_tuple(98, 'b'))),
//         "{(97,'a'),(98,'b')}",
//         std::make_tuple('a', 98)
//       );
//     }
//   }
// }
