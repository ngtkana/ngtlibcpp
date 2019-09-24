template < typename Map, typename Key = typename Map::key_type>
inline auto keys(Map const& v) {
  std::vector< Key > ret(v.size());
  std::transform(v.begin(), v.end(), ret.begin(), [](auto&& t){ return t.first; });
  return ret;
}
