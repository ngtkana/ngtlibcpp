template < typename Value >
auto dijkstra(std::vector< std::vector< std::pair< int, Value > > > const & graph, int start, Value inf) {
  assert(2 * inf <= std::numeric_limits< Value >::max());
  std::vector< Value > dist(graph.size(), inf);
  std::priority_queue< std::pair< Value, int >,
    std::vector< std::pair< Value, int > >,
    std::greater< std::pair< Value, int > > > que;
  que.emplace(0, start);
  while (!que.empty()) {
    Value d; int crr; std::tie(d, crr) = que.top(); que.pop();
    if (dist.at(crr) <= d) continue;
    dist.at(crr) = d;
    for (auto pair : graph.at(crr)) {
      Value cost; int nxt; std::tie(nxt, cost) = pair;
      if (dist.at(nxt) - d <= cost) continue;
      que.emplace(d + cost, nxt);
    }
  }
  return dist;
}
