class centroid_tree {
  const int n;
  const vector<vector<int>> grh;
  vector<bool> ckd;
  vector<int> prt, dpt;
  vector<vector<int>> cld, acs, dst, sct;
  queue<tuple<int, int, int>> que;
  int whole_ctr = -1;

  int dfs (
      const int crr,
      const int prv,
      const int bkt,
      vector<int>& sz
    )
    {
      for (auto const& nxt : grh[crr]) if (nxt != prv && !ckd[nxt]) {
        int x = dfs(nxt, crr, bkt, sz); if (x != -1) return x;
        sz[crr] += sz[nxt];
      }
      if (sz[crr] * 2 >= bkt) {
        for (auto const& nxt : grh[crr]) if (nxt != prv && !ckd[nxt]) {
          que.emplace(crr, nxt, sz[nxt]);
        }
        if (!ckd[prv]) {
          que.emplace(crr, prv, bkt - sz[crr]);
        }
        ckd[crr] = true;
        return crr;
      }
      return -1;
    }
  
  void build_centroid_tree ()
    {
      que.emplace(-1, 0, n);
      while (!que.empty()) {
        int u, rt, bkt; tie(u, rt, bkt) = que.front(); que.pop();
        vector<int> sz(n, 1);
        int l = dfs(rt, rt, bkt, sz);
        if (u == -1) {
          whole_ctr = l;
          prt[l] = l;
          dpt[l] = 0;
        } else if (u != l) {
          cld[u].push_back(l);
          prt[l] = u;
          dpt[l] = dpt[u] + 1;
        }
      }
    }
  
  void efs (
      const int rt,
      const int rt_dpt,
      int crr,
      int prv
    )
    {
      for (auto const& nxt : grh[crr]) if (nxt != prv && dpt[nxt] > rt_dpt) {
        dst[nxt][dpt[nxt] - rt_dpt] = dst[crr][dpt[crr] - rt_dpt] + 1;
        efs(rt, rt_dpt, nxt, crr);
      }
    }
  
  void calc_dst ()
    {
      for (int i = 0; i < n; i++) {
        acs[i].resize(dpt[i] + 1);
        dst[i].resize(dpt[i] + 1);
      }
      for (int rt = 0; rt < n; rt++) {
        efs(rt, dpt[rt], rt, rt);
      }
    }
  
  int ancestor (
      int x,
      int i
    )
    {
      assert (0 <= i && i <= dpt[x]);
      while (i--) {
        x = prt[x];
      }
      return x;
    }
  
  void calc_sct ()
    {
      for (int x = 0; x < n; x++) {
        for (int i = 0; i < dpt[x]; i++) {
          int a = ancestor(x, i);
          int d = dst[x][i + 1];
          { // debug
            cout
              << "x = " << x << ", "
              << "a = " << a << ", "
              << "d = " << d
              << endl;
          } //
          if ((int)sct[a].size() < d) sct[a].resize(d + 1, 0);
          sct[a][d]++;
        }
      }
    }
  
  void build ()
    {
      build_centroid_tree();
      calc_dst();
      calc_sct();
    }

  public:
    centroid_tree (
        vector<vector<int>> grh
      ) :
      n(grh.size()),
      grh(grh), ckd(n, false),
      prt(n), dpt(n),
      cld(n), acs(n), dst(n), sct(n)
      {
        build();
        { // debug
          cout << "--------------------------------------" << endl;
          cout << setw(5) << left << "sct";
          for (int i = 0; i < (int)sct.size(); i++) {
            if (i != 0) cout << setw(5) << " ";
            cout << "i = " << setw(2) << right << i << ": ";
            for (int j = 0; j < (int)sct[i].size(); j++) {
              cout << setw(4) << right << sct[i][j];
              if (j != (int)sct[i].size() - 1) cout << " ";
            }
            cout << endl;
          }
          cout << "--------------------------------------" << endl;
        } //
      }
    
    auto const& child (
        int x
      ) const
      {
        return cld[x];
      }

    auto const& parent (
        int x
      ) const
      {
        return prt[x];
      }

    auto const& depth (
        int x
      ) const
      {
        return dpt[x];
      }

    auto const& centroid (
        const int x
      ) const
      {
        return whole_ctr;
      }
};