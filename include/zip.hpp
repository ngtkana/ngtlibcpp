template < template < typename ... > class Container, typename ... Args >
auto zip(Container< Args > const& ... args) {
    auto n = std::min({args.size() ... });
    assert(n == std::max({args.size() ... }));
    Container< std::tuple< Args ... >> ret(n);
    for (std::size_t i = 0; i < n; i++)
        { ret.at(i) = {args.at(i) ...}; }
    return ret;
}