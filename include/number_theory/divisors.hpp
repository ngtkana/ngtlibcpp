inline auto divisors(int x) {
  std::vector< int > ret;
  std::stack < int > stk;
  for (auto i = 1; i * i <= x; i++) {
    if (x % i == 0) {
      ret.emplace_back(i);
      if (i * i < x)
        { stk.emplace(x / i); }
    }
  }
  while (!stk.empty())
    { ret.emplace_back(stk.top()), stk.pop(); }
  return ret;
}
