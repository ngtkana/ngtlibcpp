template <typename T, typename U>
class minimum_cost_flow {
  public:
    const T max_flow = numeric_limits<T>::max();
    const U max_dist  = numeric_limits<U>::max();
  private:
    struct edge {
      int to; T cap; U cost;
      weak_ptr<edge> rev;
    };
    const int n, source, sink;
    std::vector<U> dst;
    std::vector<std::vector<shared_ptr<edge>>> grh;
    void bf () {
      dst.assign(n, max_dist); dst[source] = 0;
      for (int t = 0; t < n; t++) {
        bool flg = false;
        for (int i = 0; i < n; i++) {
          for (auto const& e : grh[i]) {
            if (e->cap == 0) continue;
            int crr = i;     U crd = dst[crr];
            int nxt = e->to; U nxd = crd + e->cost;
            if (crd == max_dist) continue;
            if (cmn(dst[nxt], nxd)) flg = true;
          }
        }
        if (!flg) break;
        if (t == n - 1 && flg) assert(false);
      }
    }
    U flush () {
      std::vector<bool> ckd(n, false);
      return fix([&] (auto dfs, int crr, U f) -> U {
        if (ckd[crr]) return 0;
        ckd[crr] = true;
        if (crr == sink) return f;
        for (auto const& e : grh[crr]) {
        if (e->cap == 0) continue;
          U crd = dst[crr];
          int nxt = e->to; U nxd = dst[nxt];
          if (crd + e->cost != nxd) continue;
          U d = dfs(nxt, min(f, e->cap));
          if (d > 0) {
            e->cap -= d;
            e->rev.lock()->cap += d;
            return d;
          }
        }
        return 0;
      })(source, max_flow);
    }
  public:
    minimum_cost_flow (int n, int source, int sink) :
      n(n), source(source), sink(sink), grh(n)
      {}
    void insert(int u, int v, T cap, U cost) {
      auto e = make_shared<edge>(edge{v, cap, cost});
      auto r = make_shared<edge>(edge{u, 0, -cost});
      e->rev = r;
      r->rev = e;
      grh[u].push_back(e);
      grh[v].push_back(r);
    }
    T cal(U required_flow) {
      T ret = 0;
      while (true) {
        bf();
        if (dst[sink] == max_dist) break;
        T d = dst[sink]; U f = flush();
        if (f >= required_flow) {
          ret += d * required_flow;
          return ret;
        } else {
          ret += d * f;
          required_flow -= f;
        }
      }
      return -1;
    }
};