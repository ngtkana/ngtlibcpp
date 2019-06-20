vector<bool> ckd(${1:n}, false);
fix ([&](auto dfs, int crr) -> void {
  if (ckd[crr]) return;
  ckd[crr] = true;
  for (auto const& nxt : grh[crr]) {
    dfs(nxt);
  }
})(${2:0});