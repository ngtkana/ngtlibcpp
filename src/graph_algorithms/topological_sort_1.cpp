class topological_sort {
  const int n;
  const vector<vector<int>>& grh;
  vector<int> srd;
  vector<int> ckd;
  bool flg;

  bool dfs (int crr) {
    if (ckd[crr] == 1) return true;
    if (ckd[crr] == 2) return false;
    bool ret = false;
    ckd[crr] = 1;
    for (int nxt : grh[crr]) {
      ret |= dfs(nxt);
    }
    ckd[crr] = 2;
    srd.insert(srd.begin(), crr);
    return ret;
  }

  public:
    topological_sort (
        const vector<vector<int>>& grh
      ) :
      n(grh.size()),
      grh(grh),
      srd(),
      ckd(n, 0),
      flg(false)
      {
        for (int i = 0; i < n; i++) {
          flg |= (ckd[i] == 0 && dfs(i));
        }
      }
    bool has_cycle () {return flg;}
    auto sorted() const -> const vector<int>& {return srd;} 
};