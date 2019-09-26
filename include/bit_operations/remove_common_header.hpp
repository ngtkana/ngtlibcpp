auto remove_common_header(lint x, lint y) {
  auto mask = std::numeric_limits< lint >::max() >> (__builtin_clzll(x ^ y) - 1);
  return std::make_tuple(x & mask, y & mask, mask);
}
