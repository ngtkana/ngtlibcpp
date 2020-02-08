auto is_tree(std::vector< std::vector< int > > const & graph) {
    int n = graph.size();
    std::vector< int > ckd(n, false);
    auto dfs = [&] (auto&& f, int crr, int prt) -> bool {
        ckd.at(crr) = true;
        for (auto nxt : graph.at(crr)) {
            if (ckd.at(nxt)) {
                if (nxt == prt) continue;
                return true;
            }
            f(f, nxt, crr);
        }
        return false;
    };
    auto has_cycle     = dfs(dfs, 0, 0);
    auto is_spanning = std::all_of(all(ckd), [](auto x){ return x; });
    return !has_cycle && is_spanning;
}
