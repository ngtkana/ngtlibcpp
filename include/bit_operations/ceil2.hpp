long long ceil2(long long x) {
  if (x == 0 || x == 1) return 1LL;
  return (std::numeric_limits< long long >::max() >> __builtin_clzll(x - 1) - 1) + 1;
}
int ceil2(int x) {
  if (x == 0 || x == 1) return 1;
  return (std::numeric_limits< int >::max() >> __builtin_clz(x - 1) - 1) + 1;
}
