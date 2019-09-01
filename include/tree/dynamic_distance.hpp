template <typename Cost>
class dynamic_distance {
    struct edge {
        int to; Cost cost;
        edge(int to, Cost cost) : to(to), cost(cost){}
    };
    int                            n, lg;
    std::vector<std::vector<edge>> graph;
    std::vector<int>               level;
    std::vector<Cost>              depth;
    std::vector<int>               prt;
    std::vector<std::vector<int>>  tab;

    auto lca (int u, int v) const -> int {
        if (level.at(u) > level.at(v)) std::swap(u, v);
        auto d = level.at(v) - level.at(u);
        if (d > 0) {
          for (int p = lg, q = std::pow(2, lg); p >= 0; p--, q /= 2) {
            if (d > q) v = tab.at(p).at(v), d -= q;
          }
          v = prt.at(v), d--;
        }
        assert(d == 0);
        assert(level.at(u) == level.at(v));
        if (u == v) return u;
        for (int p = lg, q = std::pow(2, lg); p >= 0; p--, q /= 2) {
          auto next_u = tab.at(p).at(u);
          auto next_v = tab.at(p).at(v);
          if (next_u != next_v) u = next_u, v = next_v;
        }
        assert(u != v);
        u = prt.at(u), v = prt.at(v);
        assert(u == v);
        return u;
      }

  public:
    dynamic_distance(int n) :
      n     (n),
      lg    (std::log2(n)),
      graph (n),
      level (n, 0),
      depth (n, 0),
      prt   (n, -1),
      tab   (lg + 1, std::vector<int>(n)) {}

    void insert (int u, int v, Cost cost = 1) {
      graph.at(u).emplace_back(v, cost);
      graph.at(v).emplace_back(u, cost);
    }

    void build (int root = 0) {
      prt.at(root) = root;
      std::queue<int> que;
      que.emplace(root);
      while (!que.empty()) {
        auto crr = que.front(); que.pop();
        for (auto e : graph.at(crr)) {
          if (prt.at(e.to) != -1) continue;
          prt.at(e.to) = crr;
          level.at(e.to) = level.at(crr) + 1;
          depth.at(e.to) = depth.at(crr) + e.cost;
          que.emplace(e.to);
        }
      }
      assert(std::none_of(prt.begin(), prt.end(), [](auto x){ return x == -1; }));
      tab.at(0) = prt;
      for (auto i = 0; i < lg - 1; i++) {
        auto& crr = tab.at(i);
        auto& nxt = tab.at(i + 1);
        for (auto x = 0; x < n; x++) {
          nxt.at(x) = crr.at(crr.at(x));
        }
      }
    }

    auto operator() (int u, int v) const -> Cost {
      return depth.at(u) + depth.at(v) - 2 * depth.at(lca(u, v));
    }
};
