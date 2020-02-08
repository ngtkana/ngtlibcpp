auto suffix_array( std::string const& s) {
    int n = s.size();
    std::vector< int > ret(n, 0), rank(n, 0);
    std::iota(ret.begin(), ret.end(), 0);
    for (auto i = 0; i < n; i++)
        { rank.at(i) = s.at(i); }
    auto comb = 1;
    auto cmp = [&](auto i, auto j) {
        if (rank.at(i) < rank.at(j)) return true;
        if (rank.at(i) > rank.at(j)) return false;
        if (n <= i + comb) return true;
        if (n <= j + comb) return false;
        return rank.at(i + comb) < rank.at(j + comb);
    };
    std::vector< int > buff(n);
    for (; comb < n; comb *= 2) {
        std::sort(ret.begin(), ret.end(), cmp);
        buff.at(ret.front()) = 0;
        for (auto i = 1; i < n; i++) {
            buff.at(ret.at(i)) = buff.at(ret.at(i - 1)) + cmp(ret.at(i - 1), ret.at(i));
        }
        buff.swap(rank);
    }
    for (auto i = 0; i < n; i++)
        { rank.at(ret.at(i)) = i; }
    return ret;
}
