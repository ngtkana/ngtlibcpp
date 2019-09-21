template < typename Container, typename = typename Container::value_type >
inline auto extend(Container const& v, int k) {
  auto ret = Container(k);
  for (auto i = 0; i < k; i++)
    { ret.at(i) = v.at(i % (int)v.size()); }
  return ret;
}
