void ${1:dfs} (
  vector<vector<int>>& grh,
  vector<int>& ckd,
  int crr = ${2:0}
) {
  ckd[crr] = true;
  for (int nxt : grh[crr]) if (!ckd[nxt]) {
    $1(grh, ckd, crr);
  }
}
