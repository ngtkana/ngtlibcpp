template < class Value >
class lowest_common_ancestor {
    struct edge {
      int to; Value cost;
      edge(int to, Value cost) : to(to), cost(cost){}
    };
    int n, lg, powlg;
    std::vector< std::vector< edge > > graph;
    std::vector< int >                 depth;
    std::vector< Value >               w_depth;
    std::vector< std::vector< int > >  table;
    std::vector< int > &               tail;

  public:
    using cost_type = Value;
    lowest_common_ancestor(int n) :
      n(n),
      lg(std::log2(n)),
      powlg(std::pow(2, lg)),
      graph(n),
      depth(n, 0),
      w_depth(n, 0),
      table(lg + 1, std::vector< int >(n)),
      tail(table.back())
      {}

    void insert (int u, int v, Value cost = 1) {
      graph.at(u).emplace_back(v, cost);
      graph.at(v).emplace_back(u, cost);
    }

    void build (int root = 0) {
      auto dfs = [&](auto f, int crr, int p) -> void {
        tail.at(crr) = p;
        for (auto const& e : graph.at(crr)) {
          if (e.to == p) continue;
          depth.at(e.to) = depth.at(crr) + 1;
          w_depth.at(e.to) = w_depth.at(crr) + e.cost;
          f(f, e.to, crr);
        }
      };
      dfs(dfs, root, root);
      for (int p = lg; p >= 1; p--) {
        auto & crr = table.at(p);
        auto & nxt = table.at(p - 1);
        for (int i = 0; i < n; i++) {
          nxt.at(i) = crr.at(crr.at(i));
        }
      }
    }

    auto query(int u, int v) const -> int {
      if (depth.at(u) < depth.at(v)) std::swap(u, v);
      auto diff = depth.at(u) - depth.at(v);
      if (diff > 0) {
        int coeff = powlg;
        for (auto const & row : table) {
          if (coeff < diff) {
            u = row.at(u);
            diff -= coeff;
          }
          coeff /= 2;
        }
        u = tail.at(u);
        diff--;
      }
      assert(diff == 0);
      assert(depth.at(u) == depth.at(v));
      if (u == v) return u;
      for (auto const & row : table) {
        auto next_u = row.at(u);
        auto next_v = row.at(v);
        if (next_u != next_v) {
          u = next_u;
          v = next_v;
        }
      }
      assert(u != v);
      u = tail.at(u), v = tail.at(v), assert(u == v);
      return u;
    }

    auto row_distance (int u, int v) const -> int {
      return depth.at(u) + depth.at(v) - 2 * depth.at(query(u, v));
    }

    auto weighted_distance (int u, int v) const -> Value {
      return w_depth.at(u) + w_depth.at(v) - 2 * w_depth.at(query(u, v));
    }
};
