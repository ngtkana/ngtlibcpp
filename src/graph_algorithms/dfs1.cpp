fix ([&](auto dfs, int crr, int prt) -> void {
  for (auto const& nxt : grh[crr]) if (nxt != prt) {
    dfs(nxt, crr);
  }
})(${1:0}, $1);