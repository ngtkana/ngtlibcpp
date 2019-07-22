fix ([&](auto dfs, int crr, int p) -> void {
  for (auto const& nxt : graph.at(crr)) {
    if (nxt == p) continue;
    dfs(nxt, crr);
  }
})(${1:root}, $1);