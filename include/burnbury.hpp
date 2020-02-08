template <typename Value>
struct residue_edge {
    int to; Value cap, original_cap; int rev;
    residue_edge(int to, Value cap, int rev):
        to(to), cap(cap), original_cap(cap), rev(rev){}
};

template <typename Value>
std::ostream& operator<< (std::ostream& os, const residue_edge<Value>& e)
    { return os << "residue_edge{" << "to:" << e.to << "," << "cap:" << e.cap << "," << "rev:" << e.rev << "}"; }

template < typename Value >
struct flow_edge {
    int to; Value flow;
    flow_edge(int to, Value flow) : to(to), flow(flow){}
};
template < typename Value >
std::ostream& operator<< (std::ostream& os, const flow_edge<Value>& e)
    { return os    << "flow_edge{"    << "to:" << e.to << ","    << "flow:" << e.flow    << "}"; }

template < typename Value >
class burnbury {
        int                                 n, source, sink;
        Value                             offset;
        std::vector< bool > ckd;
        std::vector< int >    level;
        std::vector< std::vector< residue_edge< Value > > > graph;

        static constexpr Value inf_flow = std::numeric_limits< Value >::max();

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

        auto dfs (int crr, Value f = inf_flow) {
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
            return Value(0);
        }

    public:
        burnbury(int n, int source, int sink):
            n(n), offset(0), source(source), sink(sink), graph(n){}

        auto make_node() {
            n++;
            graph.resize(n);
            return n - 1;
        }

        void insert(int u, int v, Value c) {
            graph.at(u).emplace_back(v, c, graph.at(v).size());
            graph.at(v).emplace_back(u, 0, graph.at(u).size() - 1);
        }

        void red_costs    (int x, Value c) { insert(source, x, c); }
        void blue_costs (int x, Value c) { insert(x, sink, c);     }
        void red_blue_costs(int x, int y, Value c) { insert(y, x, c); }
        void blue_red_costs(int x, int y, Value c) { insert(x, y, c); }
        void red_red_profits(int x, int y, Value c) {
            offset += c;
            auto z = make_node();
            blue_costs(z, c);
            red_blue_costs(z, x, inf_flow);
            red_blue_costs(z, y, inf_flow);
        }
        void blue_blue_profits(int x, int y, Value c) {
            offset += c;
            auto z = make_node();
            red_costs(z, c);
            blue_red_costs(z, x, inf_flow);
            blue_red_costs(z, y, inf_flow);
        }

        auto build() {
            Value ret = 0;
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
            std::vector<std::vector<flow_edge<Value>>> ret(n);
            for (auto i = 0; i < n; i++) {
                for (auto const& e : graph.at(i)) {
                    auto flow = e.original_cap - e.cap;
                    if (flow > 0) ret.at(i).emplace_back(e.to, flow);
                }
            }
            return ret;
        }
};
