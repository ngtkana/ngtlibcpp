template <typename T>
class ford_fulkerson {
  struct edge {
    int to; T cap;
    weak_ptr<edge> rev;
    edge(int to, T cap) : to(to), cap(cap) {}
  };
  const int n, source, sink;
  std::vector<bool> ckd;
  std::vector<std::vector<shared_ptr<edge>>> grh;
  static constexpr T inf = numeric_limits<T>::max();
  T dfs () {
    return fix ([&](auto dfs, int crr, int f = inf) -> T {
      if (crr == sink) return f;
      ckd[crr] = true;
      for (auto& e : grh[crr]) {
        if (ckd[e->to] || !e->cap) continue;
        T d = dfs(e->to, min(f, e->cap));
        if (d) {
          e->cap -= d;
          e->rev.lock()->cap += d;
          return d;
        }
      }
      return 0;
    })(source);
  }
  public:
    ford_fulkerson (int n, int source, int sink) :
      n(n), source(source), sink(sink), grh(n)
      {}
    void insert(int u, int v, T c) {
      auto e = make_shared<edge>(v, c);
      auto r = make_shared<edge>(u, 0);
      e->rev = r;
      r->rev = e;
      grh[u].push_back(e);
      grh[v].push_back(r);
    }
    T cal() {
      T ret = 0;
      while (true) {
        ckd.assign(n, false);
        T f = dfs();
        if (!f) return ret;
        ret += f;
      }
    }
};