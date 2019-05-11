class calculate_depths {
  const int n, r;
  vector<int> dpt;
  const vector<vector<int>> grh;

  void dfs (
      const vector<vector<int>>& grh,
      vector<int>& dpt,
      int crr, int prt
    ) {
      for (int const& nxt : grh[crr]) {
        if (nxt == prt) continue;
        dpt[nxt] = dpt[crr] + 1;
        dfs(grh, dpt, nxt, crr);
      }
    }

  public:
    calculate_depths (
        const vector<vector<int>>& grh,
        const int root
      ) :
      n(grh.size()), r(root),
      dpt([&](){
          vector<int> ret(n, 0);
          dfs(grh, ret, r, r);
          return ret;
        }()),
      grh(grh)
      {
      }

    int depth (int x) const {return dpt[x];}
};