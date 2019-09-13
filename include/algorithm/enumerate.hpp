template < template < typename ... > class Container, typename T >
auto enumerate(Container< T > const& v) {
  auto n = v.size();
  Container< std::pair< int, T >> ret(n);
  for (std::size_t i = 0; i < n; i++)
    { ret.at(i) = {i, v.at(i)}; }
  return ret;
}