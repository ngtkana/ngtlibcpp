fix ([&](auto dfs, int crr) -> void {
  ckd.at(crr) = true;
  for (auto const& nxt : graph.at(crr)) {
    if (ckd.at(nxt)) continue;
    dfs(nxt);
  }
})(${1:root});