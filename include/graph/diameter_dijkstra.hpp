template < class Value >
auto diameter_dijkstra(std::vector< std::vector< std::pair< int, Value > > > graph) {
  int n = graph.size();
  auto inf = std::numeric_limits< Value >::max();
  Value ret = 0;
  std::vector< Value > dist(n, inf);
  for (auto i = 0; i < n; i++) {
    std::priority_queue<
      std::pair< Value, int >,
      std::vector < std::pair< Value, int > >,
      std::greater< std::pair< Value, int > > > que;
    auto root = i;
    dist.assign(n, inf);
    que.emplace(0, root);
    dist.at(root) = 0;
    while (!que.empty()) {
      Value d; int crr; std::tie(d, crr) = que.top(); que.pop();
      for (auto pair : graph.at(crr)) {
        int nxt; Value w; std::tie(nxt, w) = pair;
        auto e = d + w;
        if (e < dist.at(nxt)) {
          dist.at(nxt) = e;
          que.emplace(e, nxt);
        }
      }
    }
    for (auto d : dist)
      { ret = std::max(ret, d); }
  }
  return ret;
}
