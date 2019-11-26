template < typename Container, typename Value = typename Container::value_type >
auto max_rangesum(Container v) {
  assert(!v.empty());
  std::partial_sum(v.begin(), v.end(), v.begin());
  v.insert(v.begin(), 0);
  Value min = v.front();
  Value ret = v.at(1) - v.at(0);
  for (auto x : v) {
    ret = std::max(ret, x - min);
    min = std::min(min, x);
  }
  return ret;
}
