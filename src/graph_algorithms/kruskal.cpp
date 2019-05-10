template<typename T>
struct kruskal {
  using edge_type = tuple<T, int, int>;
  const int n;
  vector<edge_type> edg;
  vector<edge_type> mst;
  T weight_of_mst;
  kruskal (
      int n,
      vector<edge_type> edg
    ) :
    n(n),
    edg(edg),
    mst(n - 1),
    weight_of_mst(0)
    {
      sort(edg.begin(), edg.end());
      disjoint_set djs(n);
      int cnt = 0;
      for (auto e : edg) {
        T w; int s, t; tie(w, s, t) = e;
        if (djs.unite(s, t)) {
          weight_of_mst += w;
          mst[cnt] = {w, s, t};
          if (++cnt == n - 1) break;
        }
      }
      if (cnt < n - 1) assert(false);
    }    
};