inline auto factor(int x) {
  std::vector< std::pair< int, int > > ret{};
  for (auto p = 2; p * p <= x; p++) {
    auto m = 0;
    for (; x % p == 0; m++)
      { x /= p; }
    if (m > 0)
      { ret.emplace_back(p, m); }
  }
  if (1 < x)
    { ret.emplace_back(x, 1); }
  return ret;
}
