template <typename T>
class bellman_ford {
  using edge_t = tuple<T, int, int>;
  const int n, r;
  const std::vector<edge_t>& edg;
  bool flg;
  std::vector<long long> dst;
  void cal () {
      dst[r] = 0;
      for (int q = n; q--;) {
        flg = false;
        for (auto const& e : edg) {
          T d; int s, t; std::tie(d, s, t) = e;
          if (dst[s] == inf) continue;
          if (cmn(dst[t], dst[s] + d)) flg = true;
        }
      }
  }
  public:
    const T inf;
    bellman_ford (
        const int n, const int r,
        const std::vector<edge_t>& edg,
        const T inf = numeric_limits<T>::max()
      ) :
      n(n), r(r), edg(edg), 
      flg(false), dst(n, inf), inf(inf)
      {
        cal();
      }
    bellman_ford (
        const int n, const int r,
        const std::vector<edge_t>& edg
      ) :
      bellman_ford(n, r, edg, numeric_limits<T>::max())
      {
      }
    bool has_negative_cycle () const {return flg;}
    auto& result () {return dst;}
};