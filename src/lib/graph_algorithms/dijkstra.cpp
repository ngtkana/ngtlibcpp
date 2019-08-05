template <typename T>
class dijkstra {
  const int n, r;
  const std::vector<std::vector<std::pair<T, int>>>& grh;
  std::vector<T> dst;
  void cal () {
    priority_queue<
      std::pair<T, int>, std::vector<std::pair<T, int>>, greater<std::pair<T, int>>
      > que;
    que.emplace(0, r);
    while (!que.empty()) {
      T crd; int crr; std::tie(crd, crr) = que.top(), que.pop();
      if (!cmn(dst[crr], crd)) continue;
      for (auto e : grh[crr]) {
        T w; int nxt; std::tie(w, nxt) = e;
        T nxd = crd + w;
        if (nxd < dst[nxt]) que.emplace(nxd, nxt);
      }
    }
  }
  public:
    const T inf;
    dijkstra (
        const int r,
        const std::vector<std::vector<std::pair<T, int>>>& grh,
        const T inf = numeric_limits<T>::max()
      ) :
      n(grh.size()), r(r),
      grh(grh), dst(n, inf), inf(inf)
      {
        cal();
      }
    auto result () const {return dst;}
};