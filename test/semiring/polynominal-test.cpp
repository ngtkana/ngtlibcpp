#include <catch2/catch.hpp>
#include <bits/stdc++.h>

#include <semirings/mint.hpp>
#include <semirings/polynominal.hpp>
#include <io/container_io.hpp>

TEMPLATE_TEST_CASE( "Polynominal Tests", "[polynominal]",
  int_semiring
)
{
  SECTION( "id and zero") {
    using poly = polynominal<TestType, 20>;
    REQUIRE(poly::id().degree() == 0);
    REQUIRE(poly::id().at(0)  == TestType::id());
    REQUIRE(poly::zero().degree() == -1);
    REQUIRE(poly::id() * poly::id() == poly::id());
    REQUIRE(poly::id() * poly::zero() == poly::zero());
    REQUIRE(poly::zero() * poly::id() == poly::zero());
  }
}
