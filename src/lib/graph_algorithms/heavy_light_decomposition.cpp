// Dependent libraries: Combinator.
template <typename T>
class heavy_light_decomposition {
    struct edge {size_t to; T cost;};
    bool built; size_t n;
    std::vector<std::vector<edge>> graph;
    std::vector<size_t>             prt, sub, vid, head;
    std::vector<unsigned>           unweighted_depth;
    std::vector<T>                 weighted_depth;

  public:
    using edge_type = edge;
    using cost_type = T;
    heavy_light_decomposition(size_t n) :
      built(false), n(n),
      graph(n), prt(n), sub(n, 1), vid(n), head(n),
      unweighted_depth(n, 0), weighted_depth(n, 0) {}
    
    // Get the vertex id.
    auto id (size_t u) const -> size_t {
      return vid.at(u);}

    // Insert an edge.
    void insert (size_t u, size_t v, T cost = 1) {
        assert(!built);
        graph.at(u).push_back({v, cost});
        graph.at(v).push_back({u, cost});
      }
    // Deflag the built flag.
    void deflag () {
        assert(built);
        built = false;
      }
    // Build an HL Decomposition.
    void build (size_t root = 0) {
        assert(!built); built = true;
        fix ([&](auto dfs, size_t crr, size_t p) -> void {
          prt.at(crr) = p;
          for (auto& e : graph.at(crr)) {
            if (e.to == p) continue;
            unweighted_depth.at(e.to) = unweighted_depth.at(crr) + 1;
            weighted_depth.at(e.to)   = weighted_depth.at(crr) + e.cost;
            dfs(e.to, crr);
            sub.at(crr) += sub.at(e.to);
            if (sub.at(e.to) > sub.at(graph.at(crr).front().to))
              std::swap(e, graph.at(crr).front());
          }
        })(root, root);
        size_t now = 0; head.at(root) = root;
        fix ([&](auto dfs, size_t crr, size_t p) -> void {
          vid.at(crr) = now, now++;
          for (auto const& e : graph.at(crr)) {
            if (e.to == p) continue;
            head.at(e.to) = (e.to == graph.at(crr).front().to
              ? head.at(crr) : e.to);
            dfs(e.to, crr);
          }
        })(root, root);
      }
    // Call a function f([u, v]),
    // where u and v is the original vertex id,
    // while the parameter of f is by the HLD-order. 
    template <typename F>
    auto for_each_edge (size_t u, size_t v, F f) const
      -> void
      {
        assert(built);
        while (head.at(u) != head.at(v)) {
          if (vid.at(u) > vid.at(v)) std::swap(u, v);
          f(vid.at(head.at(v)), vid.at(v));
          v = prt.at(head.at(v));
        }
        if (vid.at(u) > vid.at(v)) std::swap(u, v);
        if (u != v) f(vid.at(u) + 1, vid.at(v));
      }
    // Calculate the lowest common ancestor.
    auto lca (size_t u, size_t v) const -> size_t {
        assert(built);
        while (head.at(u) != head.at(v)) {
          if (vid.at(u) > vid.at(v)) std::swap(u, v);
          v = prt.at(head.at(v));
        }
        return vid.at(u) < vid.at(v) ? u : v;
      }
    // Calculate the count-based distance between u and v.
    auto unweighted_dist (size_t u, size_t v) const -> unsigned {
        auto& x = unweighted_depth;
        return x.at(u) + x.at(v) - 2 * x.at(lca(u, v));
      }
    // Calculate the cost-based distance between u and v.
    auto weighted_dist (size_t u, size_t v) const -> unsigned {
        auto& x = weighted_depth;
        return x.at(u) + x.at(v) - 2 * x.at(lca(u, v));
      }
};