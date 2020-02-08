// b = a * p
template < typename Value >
auto right_norm(std::vector< Value > const& a, int h) {
    int    w = a.size();
    auto b = a;
    std::vector< int > frozen(w, false);
    for (auto i = h - 1; i >= 0; i--) {
        auto pivot = -1;
        for (auto j = 0; j < w; j++) {
            if (!frozen.at(j) && (b.at(j) & (1LL << i)))
                { pivot = j; break; }
        }
        if (pivot == -1) continue;
        frozen.at(pivot) = true;
        for (auto j = 0; j < w; j++) {
            if (j != pivot && (b.at(j) & (1LL << i)))
                { b.at(j) ^= b.at(pivot); }
        }
    }
    return b;
}
