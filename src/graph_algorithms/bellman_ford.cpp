template<typename T>
struct bellman_ford {
  using edge_type = tuple<T, int, int>;
  const int n;
  const int r;
  const vector<edge_type>& edg;
  const T inf;
  bool flg;
  vector<long long> dst;
  bellman_ford (
      int n,
      int root,
      const vector<edge_type>& edg,
      const T inf
    ) :
    n(n),
    r(root),
    edg(edg),
    inf(inf),
    flg(false),
    dst(n, inf)
    {
      dst[r] = 0;
      for (int q = n; q--;) {
        flg = false;
        for (auto const& e : edg) {
          T d; int s, t; tie(d, s, t) = e;
          if (dst[s] == inf) continue;
          if (chmin(dst[t], dst[s] + d)) flg = true;
        }
      }
    }
  bool has_negative_cycle () const {return flg;}
};