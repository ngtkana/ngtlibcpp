class least_common_ancestor {
  const int n, r;
  int ht;
  std::vector<int> dpt;
  std::vector<std::vector<int>> prt;
  const std::vector<std::vector<int>> grh;

  void dfs (
      const std::vector<std::vector<int>>& grh,
      std::vector<int>& dpt,
      int crr, int prt
    ) {
      for (int const& nxt : grh[crr]) {
        if (nxt == prt) continue;
        dpt[nxt] = dpt[crr] + 1;
        dfs(grh, dpt, nxt, crr);
      }
    }
    void climb (int& x, int b) const {
      for (int i = 0; b; i++, b >>= 1) {
        if (b & 1) x = prt[i][x];
      }
    }

  public:
    least_common_ancestor (
        const std::vector<std::vector<int>>& grh,
        const std::vector<int>& direct_prt,
        const int root
      ) :
      n(direct_prt.size()), r(root),
      ht([&, i = 0]() mutable {
          for (int p = 1; p < n; p <<= 1) i++;
          return i;
        }()),
      dpt([&](){
          std::vector<int> ret(n, 0);
          dfs(grh, ret, r, r);
          return ret;
        }()),
      prt([&](){
          std::vector<std::vector<int>> ret(ht, direct_prt);
          for (int i = 1; i < ht; i++) {
            for (int j = 0; j < n; j++) {
              prt[i][j] = prt[i - 1][prt[i - 1][j]];
            }
          }
          return ret;
        }()),
      grh(grh)
      {
      }

    int higher_prt (int x, int b) const {climb(x, b); return x;}
    int depth (int x) const {return dpt[x];}
    int lca (int x, int y) {
      if (dpt[x] < dpt[y]) climb(y, dpt[y] - dpt[x]);
      else if (dpt[y] < dpt[x]) climb(x, dpt[x] - dpt[y]);
      if (x == y) return x;
      for (int i = ht - 1; i >= 0; i--) {
        if (prt[i][x] != prt[i][y]) {
          x = prt[i][x];
          y = prt[i][y];
        }
      }
      return prt[0][x];
    }
};