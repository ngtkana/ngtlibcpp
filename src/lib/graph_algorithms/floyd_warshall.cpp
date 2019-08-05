template<typename T>
struct floyd_warshall {
  const int n;
  const T inf;
  std::vector<std::vector<T>> dst;
  void cal () {
    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (dst[i][k] != inf && dst[k][j] != inf) {
            cmn(dst[i][j], dst[i][k] + dst[k][j]);
          }
        }
      }
    }
  }
  floyd_warshall (
      const std::vector<std::vector<T>> adj,
      const T inf
    ) :
    n(adj.size()), inf(inf), dst(adj)
    {
      cal();
    }
  auto& result () {return dst;}
  bool has_negative_cycle () {
    for (int i = 0; i < n; i++) if (dst[i][i] < 0) return true;
    return false;
  }
};