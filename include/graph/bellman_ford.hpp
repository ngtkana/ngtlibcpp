template < class Value >
inline auto bellman_ford(std::vector< std::tuple< int, int, Value > > const & edges,
  int n, int start, Value inf)
{
  assert(inf <= std::numeric_limits< Value >::max());
  std::vector< Value > dist(n, inf);
  dist.at(start) = 0;
  auto relax = [&] {
    auto flag = false;
    for (auto const & edge : edges) {
      int u, v; Value d; std::tie(u, v, d) = edge;
      auto x = dist.at(u);
      auto & y = dist.at(v);
      if (x != inf && x + d < y) {
        y = x + d;
        flag = true;
      }
    }
    return flag;
  };
  for (auto i = 0; i < n; i++) { relax(); }
  auto has_cycle = relax();
  return std::make_pair(dist, has_cycle);
}
