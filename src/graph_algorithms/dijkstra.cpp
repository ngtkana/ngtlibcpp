template <typename T>
struct dijkstra {
  const int n;
  const int r;
  const T inf;
  const vector<vector<pair<T, int>>>& grh;
  vector<T> dst;
  dijkstra (
      const vector<vector<pair<T, int>>>& grh,
      const int root,
      const T inf
    ) :
    n(grh.size()),
    r(root),
    inf(inf),
    grh(grh),
    dst(n, inf)
    {
      priority_queue<
        pair<T, int>,
        vector<pair<T, int>>,
        greater<pair<T, int>>
      > que;
      que.emplace(0, r);
      while (!que.empty()) {
        T crd; int crr;
        tie(crd, crr) = que.top(), que.pop();
        if (!chmin(dst[crr], crd)) continue;
        for (auto e : grh[crr]) {
          T w; int nxt; tie(w, nxt) = e;
          T nxd = crd + w;
          if (dst[nxt] > nxd) que.emplace(nxd, nxt);
        }
      }
    }
};