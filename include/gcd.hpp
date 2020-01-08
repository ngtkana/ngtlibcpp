template < typename Value >
inline auto gcd (Value a, Value b) {
  if (a < 0) a = -a;
  if (b < 0) b = -b;
  if (a < b) std::swap(a, b);
  while (b) {
    a %= b;
    std::swap(a, b);
  }
  return a;
}
