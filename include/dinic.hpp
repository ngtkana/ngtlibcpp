template <typename Flow>
struct residue_edge {
  int to; Flow cap, original_cap; int rev;
  residue_edge(int to, Flow cap, int rev):
    to(to), cap(cap), original_cap(cap), rev(rev){}
};

template <typename Flow>
std::ostream& operator<< (std::ostream& os, const residue_edge<Flow>& e){
  return os
    << "residue_edge{"
    << "to:" << e.to << ","
    << "cap:" << e.cap << ","
    << "rev:" << e.rev
    << "}";
}

template <typename Flow>
struct flow_edge {
  int to; Flow flow;
  flow_edge(int to, Flow flow) : to(to), flow(flow){}
};

template <typename Flow>
std::ostream& operator<< (std::ostream& os, const flow_edge<Flow>& e) {
  return os
    << "flow_edge{"
    << "to:" << e.to << ","
    << "flow:" << e.flow
    << "}";
}

template <typename Flow>
class dinic {
    int                                          n, source, sink;
    std::vector<bool>                            ckd;
    std::vector<int>                             level;
    std::vector<std::vector<residue_edge<Flow>>> graph;

    static constexpr Flow inf_flow = std::numeric_limits<Flow>::max();

    void bfs () {
      std::queue<int> que;
      que.emplace(source); level.at(source) = 0;
      while (!que.empty()) {
        auto crr = que.front(); que.pop();
        for (auto const& e : graph.at(crr)) {
          if (e.cap == 0) continue;
          int nxt = e.to;
          if (level.at(nxt) != -1) continue;
          que.push(nxt);
          level.at(nxt) = level.at(crr) + 1;
        }
      }
    }

    auto dfs (int crr, Flow f = inf_flow) {
      if (crr == sink) return f;
      ckd.at(crr) = true;
      for (auto& e : graph.at(crr)) {
        auto nxt = e.to;
        if (ckd.at(nxt) || e.cap == 0 || level.at(crr) >= level.at(nxt)) continue;
        auto d = dfs(nxt, std::min(f, e.cap));
        if (d > 0) {
          e.cap -= d;
          graph.at(nxt).at(e.rev).cap += d;
          return d;
        }
      }
      level.at(crr) = -1;
      return Flow(0);
    }

  public:
    dinic (int n, int source, int sink):
      n(n), source(source), sink(sink), graph(n){}

    void insert(int u, int v, Flow c) {
      graph.at(u).emplace_back(v, c, graph.at(v).size());
      graph.at(v).emplace_back(u, 0, graph.at(u).size() - 1);
    }

    auto build() {
      Flow ret = 0;
      while (true) {
        level.assign(n, -1);
        bfs();
        if (level.at(sink) == -1) return ret;
        ckd.assign(n, false);
        while (true) {
          auto f = dfs(source);
          if (f == 0) break;
          ret += f;
        }
      }
    }

    auto collect() const {
      std::vector<std::vector<flow_edge<Flow>>> ret(n);
      for (auto i = 0; i < n; i++) {
        for (auto const& e : graph.at(i)) {
          auto flow = e.original_cap - e.cap;
          if (flow > 0) ret.at(i).emplace_back(e.to, flow);
        }
      }
      return ret;
    }
};
