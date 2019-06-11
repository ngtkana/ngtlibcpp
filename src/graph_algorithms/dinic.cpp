template <typename T>
class dinic {
  struct edge {
    int to; T cap;
    weak_ptr<edge> rev;
  };
  const int n, source, sink;
  vector<bool> ckd;
  vector<int> dst;
  vector<vector<shared_ptr<edge>>> grh;
  static constexpr T inf = numeric_limits<T>::max();
  void bfs () {
    queue<int> que;
    que.emplace(source); dst[source] = 0;
    while (!que.empty()) {
      int crr = que.front(); que.pop();
      for (auto const& e : grh[crr]) {
        if (e->cap == 0) continue;
        int nxt = e->to;
        if (dst[nxt] != -1) continue;
        que.push(nxt); dst[nxt] = dst[crr] + 1;
      }
    }
  }
  T dfs () {
    return fix ([&](auto dfs, int crr, int f = inf) -> T {
      if (crr == sink) return f;
      ckd[crr] = true;
      for (auto& e : grh[crr]) {
        int nxt = e->to;
        if (ckd[nxt] || e->cap == 0 || dst[crr] >= dst[nxt]) continue;
        T d = dfs(nxt, min(f, e->cap));
        if (d > 0) {
          e->cap -= d;
          e->rev.lock()->cap += d;
          return d;
        }
      }
      dst[crr] = -1;
      return 0;
    })(source);
  }
  public:
    dinic (int n, int source, int sink) :
      n(n), source(source), sink(sink), grh(n)
      {}
    void insert(int u, int v, T c) {
      auto e = make_shared<edge>(edge{v, c});
      auto r = make_shared<edge>(edge{u, 0});
      e->rev = r;
      r->rev = e;
      grh[u].push_back(e);
      grh[v].push_back(r);
    }
    T cal() {
      T ret = 0;
      while (true) {
        dst.assign(n, -1);
        bfs();
        if (dst[sink] == -1) return ret;
        ckd.assign(n, false);
        while (true) {
          T f = dfs();
          if (f == 0) break;
          ret += f;
        }
      }
    }
};