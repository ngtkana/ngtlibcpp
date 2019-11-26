template < class Value >
inline auto divisors(Value x) {
  std::vector< Value > ret;
  std::stack < Value > stk;
  for (Value i = 1; i * i <= x; i++) {
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
