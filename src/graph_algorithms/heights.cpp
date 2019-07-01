template<typename T>
class calculate_heights {
  const int n;
  const std::vector<std::vector<std::pair<T, int>>>& grh;
  std::vector<T> dp, ep;

  void dfs (
      int crr = 0,
      int prt = 0
    ) {
      for (auto const& e : grh[crr]) {
        T w; int nxt; std::tie(w, nxt) = e;
        if (nxt == prt) continue;
        dfs(nxt, crr);
        chmax(dp[crr], dp[nxt] + w);
      }
    }

  void efs (
      int crr = 0,
      int prt = 0
    ) {
      std::vector<T> cld = {ep[crr]};
      for (auto const& e : grh[crr]) {
        T w; int nxt; std::tie(w, nxt) = e;
        if (nxt == prt) continue;
        cld.push_back(dp[nxt] + w);
      }
      sort(cld.begin(), cld.end(), greater<T>());
      for (auto const& e : grh[crr]) {
        T w; int nxt; std::tie(w, nxt) = e;
        if (nxt == prt) continue;
        ep[nxt] = dp[nxt] + w == cld[0] ?
            cld[1] + w : cld[0] + w;
      }
      for (auto const& e : grh[crr]) {
        T w; int nxt; std::tie(w, nxt) = e;
        if (nxt == prt) continue;
        efs(nxt, crr);
      }
      chmax(dp[crr], ep[crr]);
    }

  public:
    calculate_heights(
        std::vector<std::vector<std::pair<T, int>>>& grh
      ) :
      n(grh.size()),
      grh(grh),
      dp(n, 0),
      ep(n, 0)
      {
        dfs();
        efs();
      }
    
    auto operator[] (int i) const -> const T {return dp[i];}
};