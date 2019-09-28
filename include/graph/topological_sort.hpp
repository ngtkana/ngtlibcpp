inline auto topological_sort(std::vector< std::vector < int > > const & graph) {
  int n = graph.size();
  std::vector< int > ckd(n, 0);
  std::vector< int > sorted{};
  auto dfs = [&] (auto&& f, int crr) -> bool {
    ckd.at(crr) = 1;
    auto ret = false;
    for (auto nxt : graph.at(crr)) {
      if (ckd.at(nxt) == 1) return true;
      if (ckd.at(nxt) == 2) continue;
      ret |= f(f, nxt);
    }
    sorted.emplace_back(crr);
    ckd.at(crr) = 2;
    return ret;
  };
  for (auto i = 0; i < n; i++) {
    if (ckd.at(i) == 0 && dfs(dfs, i))
      { return std::vector< int > {}; }
  }
  std::reverse(sorted.begin(), sorted.end());
  return sorted;
}
