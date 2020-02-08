
class centroid_tree {
        int n;
        int centroid;
        std::vector< std::vector< int > > graph;
        std::vector< int > depth;
        std::vector< int > size;
        std::vector< std::vector< int > > subtrees;

        auto dead(int i) { return depth.at(i) != -1; }

        auto build_impl(int root, int n, int d) -> int {
            auto ctr = -1;
            auto dfs = [&, this](auto&& f, int crr, int prv) -> int {
                auto sz = 1;
                for (auto const nxt : graph.at(crr)) {
                    if (nxt == prv || this->dead(nxt)) continue;
                    sz += f(f, nxt, crr);
                }
                if (ctr == -1 && n <= 2 * sz)
                    { ctr = crr; }
                return size.at(crr) = sz;
            };
            dfs(dfs, root, root);

            depth.at(ctr) = d;
            for (auto const & nxt : graph.at(ctr)) {
                if (dead(nxt)) continue;
                auto sz = size.at(nxt);
                if (n <= 2 * sz)
                    { sz = n - size.at(ctr); }
                subtrees.at(ctr).emplace_back(build_impl(nxt, sz, d + 1));
            }
            size.at(ctr) = n;
            return ctr;
        }

    public:
        centroid_tree(std::vector< std::vector< int > > const& graph) :
            n(graph.size()),
            graph(graph),
            depth(n, -1),
            size(n),
            subtrees(n)
            {}

        void build() {
            centroid = build_impl(0, n, 0);
        }

        auto get_depth     () const { return depth;        }
        auto get_size        () const { return size;         }
        auto get_subtrees() const { return subtrees; }
        auto get_centroid() const { return centroid; }
};
