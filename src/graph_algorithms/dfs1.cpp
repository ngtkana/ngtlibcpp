void ${1:dfs} (
    const vector<vector<int>>& grh,
    int crr = ${2:0},
    int prt = ${2:0}
  ) {
    for (int nxt : grh[crr]) if (nxt != prt) {
      $1(grh, nxt, crr);
    }
  }
