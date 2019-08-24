#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <network_flow/dinic.hpp>

TEST_CASE( "max_flow", "[dinic]")
{
  auto dnc = dinic<int>(4, 0, 3);
  dnc.insert(0, 1, 2);
  dnc.insert(0, 2, 1);
  dnc.insert(1, 2, 1);
  dnc.insert(1, 3, 1);
  dnc.insert(2, 3, 2);
  REQUIRE(dnc.build() == 3);
}