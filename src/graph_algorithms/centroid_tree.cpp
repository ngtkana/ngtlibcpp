class centroid_tree {
  const int n;
  const vector<vector<int>> grh;
  vector<bool> ckd;
  vector<vector<int>> ctr;
  queue<tuple<int, int, int>> que;
  int rt = -1;
  int dfs (
      const int crr,
      const int prt,
      const int bkt,
      vector<int>& sz
    )
    {
      for (auto const& nxt : grh[crr]) if (nxt != prt && !ckd[nxt]) {
        int x = dfs(nxt, crr, bkt, sz); if (x != -1) return x;
        sz[crr] += sz[nxt];
      }
      if (sz[crr] * 2 >= bkt) {
        for (auto const& nxt : grh[crr]) if (!ckd[nxt]) {
          if (nxt != prt) que.emplace(crr, nxt, sz[nxt]);
          else que.emplace(crr, nxt, bkt - sz[crr]);
        }
        ckd[crr] = true;
        return crr;
      }
      return -1;
    }
  void build ()
    {
      que.emplace(-1, 0, n);
      while (!que.empty()) {
        int prv_ctr, start, bkt; tie(prv_ctr, start, bkt) = que.front(); que.pop();
        vector<int> sz(n, 1);
        int new_ctr = dfs(start, start, bkt, sz);
        if (prv_ctr == -1) rt = new_ctr;
        else ctr[prv_ctr].push_back(new_ctr);
      }
    }
  public:
    centroid_tree (
        vector<vector<int>> grh
      ) :
      n(grh.size()),
      grh(grh), ckd(n, false),
      ctr(n)
      {
        build();
      }
    auto const centroid () const {return rt;}
    auto const& result () const {return ctr;}
    auto const& operator [] (int i) const {return ctr[i];}
    auto const size () const {return n;}
};