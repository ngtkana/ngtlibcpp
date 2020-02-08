template < class Value >
auto compress (std::vector< Value > const& v) {
    int n = v.size();
    if (n == 0) return std::vector< Value >{};
    std::vector< std::pair< Value, int > > pairs(n);
    for (auto i = 0; i < n; i++)
        { pairs.at(i) = {v.at(i), i}; }
    std::sort(pairs.begin(), pairs.end());
    std::vector< Value > new_v(n);
    auto prv = pairs.at(0).first;
    auto i = 0;
    for (auto & pair : pairs) {
        Value crr; int pos; std::tie(crr, pos) = pair;
        if (prv < crr) i++;
        new_v.at(pos) = i;
        prv = crr;
    }
    return new_v;
}