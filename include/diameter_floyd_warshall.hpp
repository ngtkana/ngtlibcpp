template < class Value >
auto diameter_floyd_warshall(std::vector< std::vector< Value > > a) {
    int n = a.size();
    auto inf = std::numeric_limits< Value >::max();
    for (auto k = 0; k < n; k++) {
        for (auto i = 0; i < n; i++) {
            for (auto j = 0; j < n; j++) {
                auto & z = a.at(i).at(j);
                auto     x = a.at(i).at(k);
                auto     y = a.at(k).at(j);
                z = std::min(z, inf - x <= y
                    ? inf : x + y);
            }
        }
    }
    Value ret = 0;
    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            ret = std::max(ret, a.at(i).at(j));
        }
    }
    return ret;
}
