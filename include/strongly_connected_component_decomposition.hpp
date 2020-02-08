auto strongly_connected_component_decomposition(
    std::vector< std::vector< int > > const & graph )
{
    int const n = graph.size();
    std::vector< int > ckd(n, false);
    std::vector< int > ord;

    auto const dfs = [&graph, &ckd, &ord](auto&& f, auto crr) -> void {
        ckd.at(crr) = true;
        for (auto const nxt : graph.at(crr)) {
            if (ckd.at(nxt)) continue;
            f(f, nxt);
        }
        ord.emplace_back(crr);
    };
    for (auto i = 0; i < n; i++) {
        if (ckd.at(i)) continue;
        dfs(dfs, i);
    }
    std::reverse(ord.begin(), ord.end());

    std::vector< std::vector< int > > rgraph(n);
    for (auto i = 0; i < n; i++) {
        for (auto j : graph.at(i)) {
            rgraph.at(j).emplace_back(i);
        }
    }

    auto now = 0;
    std::vector< int > cmp(n, -1);
    auto const rdfs = [&rgraph, &cmp, &now](auto&& f, auto crr) -> void {
        cmp.at(crr) = now;
        for (auto const nxt : rgraph.at(crr)) {
            if (cmp.at(nxt) != -1) continue;
            f(f, nxt);
        }
    };
    for (auto i : ord) {
        if (cmp.at(i) != -1) continue;
        rdfs(rdfs, i);
        now++;
    }
    return cmp;
}
