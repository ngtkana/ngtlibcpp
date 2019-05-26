class centroid_tree {
  const int n;
  const vector<vector<int>> grh;
  vector<bool> ckd;
  vector<vector<int>> ctr;
  queue<tuple<int, int, int>> que;
  int rt = -1;
  void build ()
    {
      vector<int> sz(n);
      que.emplace(-1, 0, n);
      while (!que.empty()) {
        int prv_ctr, start, bkt; tie(prv_ctr, start, bkt) = que.front(); que.pop();
        int new_ctr = -1;
        make_fixed_point ([&](auto dfs, int crr, int prt) -> void {
            sz[crr] = 1;
            for (auto const& nxt : grh[crr]) if (nxt != prt && !ckd[nxt]) {
              dfs(nxt, crr); if (new_ctr != -1) return;
              sz[crr] += sz[nxt];
            }
            if (sz[crr] * 2 >= bkt) {
              for (auto const& nxt : grh[crr]) if (!ckd[nxt]) {
                if (nxt != prt) que.emplace(crr, nxt, sz[nxt]);
                else que.emplace(crr, nxt, bkt - sz[crr]);
              }
              ckd[crr] = true;
              new_ctr = crr;
            }
          })(start, start);
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