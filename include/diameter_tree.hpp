template<typename T>
class diameter_tree {
        struct edge {
            size_t to; T cost;
            edge(size_t to, T cost) : to(to), cost(cost){}
        };
        size_t n;
        std::vector<std::vector<edge>> graph;

    public:
        diameter_tree(size_t n) : n(n), graph(n){}

        // Insert an edge.
        void insert(size_t i, size_t j, T cost = 1) {
            assert(0 <= i && i < n);
            assert(0 <= j && j < n);
            graph.at(i).emplace_back(j, cost);
            graph.at(j).emplace_back(i, cost);
        };

        // Calculate the diameter_tree.
        auto operator()(size_t root = 0){
            std::vector<T> depth; 
            auto cal = [&] (size_t r) {
                depth.assign(n, 0);
                fix ([&](auto dfs, size_t crr, size_t p) -> void {
                    for (auto const& e : graph.at(crr)) {
                        if (e.to == p) continue;
                        depth.at(e.to) = depth.at(crr) + e.cost;
                        dfs(e.to, crr);
                    }
                })(r, r);
            };
            cal(root);
            auto ex = std::max_element(depth.begin(), depth.end()) - depth.begin();
            cal(ex);
            return *std::max_element(depth.begin(), depth.end());
        }
};
