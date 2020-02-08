template <typename Flow, typename Cost>
class minimum_cost_flow {
        struct edge {
            int to; Flow cap; Cost cost; int rev;
            edge(int to, Flow cap, Cost cost, int rev): to(to), cap(cap), cost(cost), rev(rev){}
        };

        const int                                            n, source, sink;
        std::vector<Cost>                            distance;
        std::vector<std::vector<edge>> graph;
        std::vector<int>                             ckd;

        const Flow max_flow = std::numeric_limits<Flow>::max();
        const Cost max_dist = std::numeric_limits<Cost>::max();

        template <typename T, typename U>
        auto cmn(T& a, U b) {if (a > b) {a = b; return true;} return false;}

        void bellman_ford() {
            distance.assign(n, max_dist);
            distance.at(source) = 0;
            for (int t = 0; t < n; t++) {
                bool renewed = false;
                for (int i = 0; i < n; i++) {
                    for (auto const& e : graph.at(i)) {
                        if (e.cap == 0) continue;
                        auto crr = distance.at(i);
                        if (crr == max_dist) continue;
                        if (cmn(distance.at(e.to), crr + e.cost)) {
                            renewed = true;
                        }
                    }
                }
                if (!renewed) break;
            }
        }

        void dijkstra() {
            distance.assign(n, max_dist);
            auto que = std::priority_queue<
                std::pair        < Cost, int >,
                std::vector    < std::pair < Cost, int > >,
                std::greater < std::pair < Cost, int >> >{};
            que.emplace(0, source);
            while (!que.empty()) {
                auto pair = que.top(); que.pop();
                auto crd = pair.first;
                auto crr = pair.second;
                if (!cmn(distance.at(crr), crd)) continue;
                for (auto e : graph.at(crr)) {
                    if (e.cap == 0) continue;
                    auto nxd = crd + e.cost;
                    if (distance.at(e.to) <= nxd) continue;
                    que.emplace(nxd, e.to);
                }
            }
        }

        auto flush_impl(int crr, Flow f) {
            if (ckd.at(crr)) return Flow(0);
            ckd.at(crr) = true;
            if (crr == sink) return f;
            for (auto & e : graph.at(crr)) {
                if (e.cap == 0) continue;
                if (distance.at(crr) + e.cost != distance.at(e.to)) continue;
                auto d = flush_impl(e.to, std::min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    graph.at(e.to).at(e.rev).cap += d;
                    return d;
                }
            }
            return Flow(0);
        }

        auto flush() {
            ckd.assign(n, false);
            return flush_impl(source, max_flow);
        }

    public:
        minimum_cost_flow(int n, int source, int sink) :
            n(n), source(source), sink(sink), graph(n) {}

        void insert(int u, int v, Flow cap, Cost cost) {
            graph.at(u).emplace_back(v, cap, cost, graph.at(v).size());
            graph.at(v).emplace_back(u, 0, -cost,    graph.at(u).size() - 1);
        }

        auto build(Flow required_flow) {
            Cost ret = 0;
            while (true) {
                bellman_ford();
                auto d = distance.at(sink);
                if (distance.at(sink) == max_dist) break;
                auto f = flush();
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