fix ([&](auto dfs, int crr, int prt) -> void {
  for (auto const& nxt : grh.at(crr)) {
    if (nxt == prt) continue;
    dfs(nxt, crr);
  }
})(${1:0}, $1);