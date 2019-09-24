template < typename Map, typename Value = typename Map::key_type>
inline auto values(Map const& v) {
  std::vector< Value > ret(v.size());
  std::transform(v.begin(), v.end(), ret.begin(), [](auto&& t){ return t.second; });
  return ret;
}
