class bipartite_matching {
        int L, R;
        std::vector<std::vector<int>> graph;
        std::vector<int> match, level;

        bool bfs() {
            std::fill(level.begin(), level.end(), -1);
            std::queue<int> que;
            for (auto i = 0; i < L; i++) {
                if (match.at(i) < 0) {
                    level.at(i) = 0;
                    que.emplace(i);
                }
            }
            bool ret = false;
            while (!que.empty()) {
                auto crr = que.front(); que.pop();
                for (auto nxt : graph.at(crr)) {
                    if (level.at(nxt) != -1) continue;
                    level.at(nxt) = level.at(crr) + 1;
                    auto w = match.at(nxt);
                    if (w == -1)
                        { ret = true; }
                    else if (level.at(w) == -1) {
                        level.at(w) = level.at(crr) + 1;
                        que.emplace(w);
                    }
                }
            }
            return ret;
        }

        bool dfs(int crr) {
            for (auto nxt : graph.at(crr)) {
                assert(level.at(nxt) <= level.at(crr) + 1);
                if (level.at(nxt) < level.at(crr) + 1) continue;
                level.at(nxt) = -1;
                auto w = match.at(nxt);
                if (w == -1 || dfs(w)) {
                    match.at(nxt) = crr;
                    match.at(crr) = nxt;
                    level.at(crr) = -1;
                    return true;
                }
            }
            level.at(crr) = -1;
            return false;
        }

    public:
        bipartite_matching()=default;
        bipartite_matching(int L, int R):
            L(L), R(R), graph(L + R), match(L + R, -1), level(L + R)
            {}

        void insert(int u, int v) {
            v += L;
            graph.at(u).emplace_back(v);
            graph.at(v).emplace_back(u);
        }


        int build () {
            auto ret = 0;
            while (bfs()) {
                for (int i = 0; i < L; i++) {
                    if (match.at(i) == -1 && dfs(i))
                        { ret++; }
                }
            }
            return ret;
        }

        auto collect() const {return match;}

        auto count() const {
            auto k = L + R - std::count(match.begin(), match.end(), -1);
            assert(k % 2 == 0);
            return k / 2;
        }
};
