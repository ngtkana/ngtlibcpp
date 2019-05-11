struct low_link_tree {
  const int n;
  const int r = 0;
  int tmr = 0;
  vector<int> ord;
  vector<int> low;
  set<int> art;
  set<pair<int, int>> bdg;
  vector<vector<int>> grh;
public:
  low_link_tree (
    vector<vector<int>> const& grh,
    const int root
  )
  : n(grh.size())
  , r(root)
  , ord(n, -1)
  , low(n, -1)
  , grh(grh)
  {
    dfs(r, r);
  }
  void dfs (
    int crr
  ,	int prt
  ) {
    int cnt = 0;
    ord[crr] = low[crr] = tmr++;
    for (int nxt : grh[crr]) {
      if (ord[nxt] == -1) {
        cnt++;
        dfs(nxt, crr);
        chmin(low[crr], low[nxt]);
        if (crr != r && ord[crr] <= low[nxt]) art.insert(crr);
        if (ord[crr] < low[nxt]) bdg.emplace(min(crr, nxt), max(crr, nxt));
      }
      if (nxt != prt) chmin(low[crr], ord[nxt]);
    }
    if (crr == r && cnt > 1) art.insert(crr);
  }
};
