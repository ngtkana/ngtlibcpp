template<typename T1, typename T2>
inline bool chmin (T1& a, T2 b) {
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}
template<typename T>
struct floyd_warshall {
  const int n;
  const T inf;
  vector<vector<T>> dst;
  floyd_warshall (
      vector<vector<T>> adj,
      const T inf
    ) :
    n(adj.size()),
    inf(inf),
    dst(adj)
    {
      for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
            if (dst[i][k] != inf && dst[k][j] != inf)
              chmin(dst[i][j], dst[i][k] + dst[k][j]);
          }
        }
      }
    }
  const bool has_negative_cycle () {
    for (int i = 0; i < n; i++) if (dst[i][i] < 0) return true;
    return false;
  }
};