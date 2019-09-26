auto ceil2(lint x) {
  if (x == 0 || x == 1) return 1LL;
  return (std::numeric_limits< lint >::max() >> __builtin_clzll(x - 1) - 1) + 1;
}
