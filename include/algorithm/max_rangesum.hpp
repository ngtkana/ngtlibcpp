template < typename Container, typename Value = typename Container::value_type >
auto max_rangesum(Container v) {
  std::partial_sum(v.begin(), v.end(), v.begin());
  auto min = Value{0};
  auto ret = -std::numeric_limits<  Value >::max();
  for (auto x : v) {
    ret = std::max(ret, x - min);
    min = std::min(min, x);
  }
  return ret;
}
