template<typename T>
class diameter {
  const int n;
  const std::vector<std::vector<std::pair<T, int>>>& grh;
  T diam;
  int ex, fx;
  void cal () {
    for (int t = 0; t < 2; t++) {
      diam = 0;
      fix ([&](auto dfs, int crr, int prt, T dpt = 0) -> void {
        if (cmx(diam, dpt)) fx = crr;
        for (auto const& e : grh[crr]) {
          T w; int nxt; std::tie(w, nxt) = e;
          if (nxt == prt) continue;
          dfs(nxt, crr, dpt + w);
        }
      })(ex, ex);
      std::swap(ex, fx);
    }
    if (ex > fx) std::swap(ex, fx);
  }
  public:
    diameter (std::vector<std::vector<std::pair<T, int>>>& grh) :
      n(grh.size()), grh(grh),
      diam(0), ex(0), fx(0)
      {
        cal();
      }
    T result () const {return diam;}
    auto extremals () const -> std::pair<int, int> {return {ex, fx};}
};