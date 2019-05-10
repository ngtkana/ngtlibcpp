class low_link_tree {
  int n;
  int tmr = 0;
  int rt = 0;
  vector<int> ord;
  vector<int> low;
  set<int> atc;
  set<pair<int, int>> bdg;
  vector<vector<int>> grh;
public:
  low_link_tree (
    vector<vector<int>> const& grh
  )
  : n(grh.size())
  , ord(n, -1)
  , low(n, -1)
  , grh(grh)
  {
    dfs(0, 0);
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
        if (crr != rt && ord[crr] <= low[nxt]) atc.insert(crr);
        if (ord[crr] < low[nxt]) bdg.emplace(min(crr, nxt), max(crr, nxt));
      }
      if (nxt != prt) chmin(low[crr], ord[nxt]);
    }
    if (crr == rt && cnt > 1) atc.insert(crr);
  }
  auto const &order() {return ord;}
  auto const &low_link() {return low;}
  auto const &articulation_points() {return atc;}
  auto const &bridges() {return bdg;}
};
