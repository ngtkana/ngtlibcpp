vector<bool> ckd(${1:n}, false);
fix ([&](auto dfs, int crr) -> void {
  ckd[crr] = true;
  for (auto const& nxt : grh[crr]) if (!ckd[nxt]) {
    dfs(nxt, crr);
  }
})(${2:0});