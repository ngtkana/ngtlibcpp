template < typename Value >
auto dijkstra(std::vector< std::vector< std::pair< Value, int > > > const & graph, int start) {
  std::vector< Value > dist(graph.size(), std::numeric_limits< Value >::max());
  std::priority_queue<
    std::pair< Value, int >,
    std::vector< std::pair< Value, int > >,
    std::greater< std::pair< Value, int > > > que;
  que.emplace(0, start);
  while (!que.empty()) {
    Value d; int crr; std::tie(d, crr) = que.top(); que.pop();
    if (dist.at(crr) <= d) continue;
    dist.at(crr) = d;
    for (auto pair : graph.at(crr)) {
      Value cost; int nxt; std::tie(cost, nxt) = pair;
      if (dist.at(nxt) - d <= cost) continue;
      que.emplace(d + cost, nxt);
    }
  }
  return dist;
}
