template < template < typename ... > class Container, typename Value >
auto runlength(Container< Value > const& v) {
  auto n = (int)v.size();
  if (n == 0)
    { return Container< std::pair< Value, int > >{}; }
  auto pos = Container< int >{};
  for (auto i = 1; i < n; i++) {
    if (v.at(i - 1) != v.at(i))
      { pos.emplace_back(i); }
  }
  pos.emplace_back(n);
  auto m = (int)pos.size();
  auto len = Container< int >(m);
  std::adjacent_difference(pos.begin(), pos.end(), len.begin());
  auto ret = Container< std::pair< Value, int > >(m);
  for (auto i = 0; i != m; i++)
    { ret.at(i) = {v.at(pos.at(i) - 1), len.at(i)}; }
  return ret;
}
