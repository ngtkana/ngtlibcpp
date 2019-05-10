void ${1:dfs} (
  int crr
, int prt
, vector<vector<int>>& grh
) {
  for (int nxt : grh[crr]) if (nxt != prt) {
    $1(nxt, crr, grh);
  }
}
