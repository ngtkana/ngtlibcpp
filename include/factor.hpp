template < class Value >
inline auto factor(Value x) {
    std::vector< std::pair< Value, int > > ret;
    for (Value p = 2; p * p <= x; p++) {
        int m = 0;
        for (; x % p == 0; m++)
            { x /= p; }
        if (m > 0)
            { ret.emplace_back(p, m); }
    }
    if (1 < x)
        { ret.emplace_back(x, 1); }
    return ret;
}
