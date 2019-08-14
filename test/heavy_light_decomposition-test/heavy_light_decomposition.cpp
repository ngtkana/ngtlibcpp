#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <tree/heavy_light_decomposition.hpp>

TEST_CASE("foo", "[Heavy-Light Decmoposition")
{
  auto hld = heavy_light_decomposition(11);
  hld.insert(0, 1);
  hld.insert(0, 2);
  hld.insert(1, 3);
  hld.insert(1, 4);
  hld.insert(1, 5);
  hld.insert(2, 6);
  hld.insert(4, 7);
  hld.insert(4, 8);
  hld.insert(8, 9);
  hld.insert(6, 10);
  hld.build();
}
