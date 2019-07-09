// Class for calculating LCA.
// Dependent libraries: Combinator.
template <typename T>
class lowest_common_ancestor {
    struct edge {
        size_t to; T cost;
        edge(size_t to, T cost) : to(to), cost(cost){}
      };
    size_t n, lg;
    std::vector<std::vector<edge>>   graph;
    std::vector<unsigned>            depth;
    std::vector<T>                   weighted_depth;
    std::vector<std::vector<size_t>> prt;
  public:
    using cost_type = T;
    lowest_common_ancestor(size_t n) :
      n(n), lg(std::log2(n)),
      graph(n), depth(n, 0), weighted_depth(n, 0),
      prt(lg + 1, std::vector<size_t>(n)) {}
    // Insert an edge.
    void insert (size_t u, size_t v, T cost = 1) {
        graph.at(u).emplace_back(v, cost);
        graph.at(v).emplace_back(u, cost);
      }
    // Build a doubling table.
    void build (size_t root = 0) {
        fix ([&](auto dfs, size_t crr, size_t p) -> void {
          prt.at(0).at(crr) = p;
          for (auto const& e : graph.at(crr)) {
            if (e.to == p) continue;
            depth.at(e.to) = depth.at(crr) + 1;
            weighted_depth.at(e.to) = weighted_depth.at(crr) + e.cost;
            dfs(e.to, crr);
          }
        })(root, root);
        for (size_t p = 1; p <= lg; p++) {
          for (size_t i = 0; i < n; i++) {
            prt.at(p).at(i) = prt.at(p - 1).at(prt.at(p - 1).at(i));
          }
        }
      }
    // Calculate the lca.
    auto operator()(size_t u, size_t v) const -> size_t {
        if (depth.at(u) < depth.at(v)) std::swap(u, v);
        auto diff = depth.at(u) - depth.at(v);
        if (diff > 0) {
          for (size_t p = lg, q = std::pow(2, lg); p <= lg; p--, q /= 2) {
            if (diff > q) u = prt.at(p).at(u), diff -= q;
          }
          u = prt.at(0).at(u), diff--;
        }
        assert(diff == 0), assert(depth.at(u) == depth.at(v));
        if (u == v) return u;
        for (size_t p = lg, q = std::pow(2, lg); p <= lg; p--, q /= 2) {
          auto next_u = prt.at(p).at(u);
          auto next_v = prt.at(p).at(v);
          if (next_u != next_v) u = next_u, v = next_v;
        }
        assert(u != v);
        u = prt.at(0).at(u), v = prt.at(0).at(v), assert(u == v);
        return u;
      }
    // Calculate the count-based distance.
    auto row_dist (size_t u, size_t v) const -> unsigned {
      return depth.at(u) + depth.at(v) - 2 * depth.at(operator()(u, v));}
    // Calculate the count-based distance.
    auto weighted_dist (size_t u, size_t v) const -> T {
      auto& x = weighted_depth;
      return x.at(u) + x.at(v) - 2 * x.at(operator()(u, v));}
};