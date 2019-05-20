make_fixed_point ([&](auto dfs, int crr, int prt) -> void {
  for (auto const& nxt : ctr[crr]) if (nxt != prt) {
    dfs(nxt, crr);
  }
})(${1:0}, ${1:0});