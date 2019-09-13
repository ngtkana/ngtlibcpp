template < template < typename ... > class Container, typename T >
auto coenumerate(Container< T > const& v) {
  auto n = v.size();
  Container< std::pair< T, int >> ret(n);
  for (std::size_t i = 0; i < n; i++)
    { ret.at(i) = {v.at(i), i}; }
  return ret;
}