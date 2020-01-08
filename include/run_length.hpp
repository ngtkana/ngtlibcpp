template < class Container, class Value = typename Container::value_type >
auto run_length(Container const& v) {
  auto n = (int)v.size();
  if (n == 0)
    { return std::vector< std::pair< Value, int > >{}; }
  auto pos = std::vector< int >{};
  for (auto i = 1; i < n; i++) {
    if (v.at(i - 1) != v.at(i))
      { pos.emplace_back(i); }
  }
  pos.emplace_back(n);
  auto m = (int)pos.size();
  auto len = std::vector< int >(m);
  std::adjacent_difference(pos.begin(), pos.end(), len.begin());
  auto ret = std::vector< std::pair< Value, int > >(m);
  for (auto i = 0; i != m; i++)
    { ret.at(i) = {v.at(pos.at(i) - 1), len.at(i)}; }
  return ret;
}
