template < class Value >
auto floyd_warshall(std::vector< std::vector< Value > > adj) {
  int n = adj.size();
  for (auto k = 0; k < n; k++) {
    for (auto i = 0; i < n; i++) {
      for (auto j = 0; j < n; j++) {
        auto & crr = adj.at(i).at(j);
        auto x = adj.at(i).at(k);
        auto y = adj.at(k).at(j);
        if (x < crr - y) {
          crr = x + y;
        }
      }
    }
  }
  return adj;
}
