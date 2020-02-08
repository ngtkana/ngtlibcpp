class two_edge_decomposition {
        int n, m;
        std::vector< std::vector< std::pair< int, int > > > graph;
        std::vector< std::pair< int, int > > edges;
        std::vector< int > ord, low, is_bridge;

        void build_low_link_impl(int root = 0) {
            is_bridge.resize(m, false);
            int ord_ = 0;
            auto dfs = [&](auto&& dfs, int crr, int prv) -> void {
                ord.at(crr) = low.at(crr) = ord_++;
                for (auto edge : graph.at(crr)) {
                    int nxt, id; std::tie(nxt, id) = edge;
                    if (nxt == prv) continue;
                    if (ord.at(nxt) != -1) {
                        low.at(crr) = std::min(low.at(crr), ord.at(nxt));
                        continue;
                    }
                    dfs(dfs, nxt, crr);
                    low.at(crr) = std::min(low.at(crr), low.at(nxt));
                    is_bridge.at(id) = ord.at(crr) < low.at(nxt);
                }
            };
            dfs(dfs, root, root);
        }

        void build_cmp_impl() {
            auto efs = [&](auto&& efs, int crr, int prv) -> void {
                cmp.at(crr) = sz;
                for (auto edge : graph.at(crr)) {
                    int nxt, id; std::tie(nxt, id) = edge;
                    if (nxt == prv
                        || is_bridge.at(id)
                        || cmp.at(nxt) != -1) continue;
                    efs(efs, nxt, crr);
                }
            };
            for (int i = 0; i < n; i++) {
                if (cmp.at(i) != -1) continue;
                efs(efs, i, i);
                sz++;
            }
        }

        void build_qgraph_impl() {
            qgraph.resize(sz);
            for (int i = 0; i < n; i++) {
                for (auto edge : graph.at(i)) {
                    int j, id; std::tie(j, id) = edge;
                    if (!is_bridge.at(id)) continue;
                    int x = cmp.at(i), y = cmp.at(j);
                    qgraph.at(x).emplace_back(y);
                    bridges.emplace_back(i, j);
                }
            }
        }

    public:
        int sz;
        std::vector< int > cmp;
        std::vector< std::pair< int, int > > bridges;
        std::vector< std::vector< int > > qgraph;

        two_edge_decomposition(int n) :
            n(n), m(0), graph(n), edges(), ord(n, -1), low(n),
            sz(0), cmp(n, -1), bridges(), qgraph(){}

        void insert(int i, int j) {
            graph.at(i).emplace_back(j, m);
            graph.at(j).emplace_back(i, m);
            edges.emplace_back(i, j);
            m++;
        }

        void build(int root = 0) {
            build_low_link_impl(root);
            build_cmp_impl();
            build_qgraph_impl();
        }
};

