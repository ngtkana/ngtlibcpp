auto diameter_bfs(std::vector< std::vector< int > > graph) {
    int n = graph.size();
    auto ret = 0;
    std::vector< int > dist(n, -1);
    for (auto root = 0; root < n; root++) {
        dist.assign(n, -1);
        std::queue< int > que;
        que.emplace(root);
        dist.at(root) = 0;
        while (!que.empty()) {
            auto crr = que.front(); que.pop();
            for (auto nxt : graph.at(crr)) {
                if (dist.at(nxt) == -1) {
                    dist.at(nxt) = dist.at(crr) + 1;
                    que.emplace(nxt);
                }
            }
        }
        for (auto d : dist)
            { ret = std::max(ret, d); }
    }
    return ret;
}
