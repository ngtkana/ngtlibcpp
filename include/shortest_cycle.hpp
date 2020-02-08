// Returns {} if no cycle
inline auto shortest_cycle (std::vector< std::vector< int > > const & graph) {
    constexpr auto inf = std::numeric_limits< int >::max();
    int n = graph.size();

    std::vector< std::vector< int > > rev(n);
    for (auto i = 0; i < n; i++) {
        for (auto j : graph.at(i)) {
            assert(i != j);                             // no self-loop allowed
            rev.at(j).emplace_back(i);
        }
    }

    auto bfs = [&] (auto start) {
        std::vector< int > dist(n, inf);
        std::queue< int > que;
        que.emplace(start);
        while (!que.empty()) {
            auto crr = que.front(); que.pop();
            auto finish = false;
            for (auto nxt : graph.at(crr)) {
                if (dist.at(nxt) != inf) continue;
                que.emplace(nxt);
                dist.at(nxt) = (crr == start ? 0 : dist.at(crr)) + 1;
                if (nxt == start) {
                    finish = true;
                    break;
                }
            }
            if (finish)
                { break; }
        }

        auto len = dist.at(start);
        if (len == inf)
            { return std::vector< int > {}; }
        auto ret = std::vector< int > (len);
        ret.front() = start;
        auto crr = start;
        for (auto d = len - 1; d >= 1; d--) {
            for (auto nxt : rev.at(crr)) {
                if (dist.at(nxt) == d)
                    { crr = nxt; break; }
            }
            ret.at(d) = crr;
        }

        // uniqueness check
        std::set< int > set;
        for (auto x : ret) set.insert(x);
        assert((int)set.size() == len);

        return ret;
    };

    auto min = inf;
    auto ret = std::vector< int >{};
    for (auto i = 0; i < n; i++) {
        auto now = bfs(i);
        if (!now.empty() && (int)now.size() < min) {
            min = now.size();
            std::swap(now, ret);
        }
    }
    return ret;
}
