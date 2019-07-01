  void dfs (
      int crr = 0,
      int prt = 0
    ) {
      for (int const& nxt : grh[crr]) {
        ${2:T} w; int nxt; std::tie(w, nxt) = e;
        if (nxt == prt) continue;
        dfs(nxt, crr);
        chmax(dp[crr], dp[nxt] + w);
      }
    }