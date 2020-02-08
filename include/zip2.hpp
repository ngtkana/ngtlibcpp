template < template < typename ... > class Container, typename T, typename U >
auto zip2(Container< T > const& x, Container< U > const& y) {
    auto n = x.size();
    auto m = y.size();
    assert(n == m);
    Container< std::pair< T, U >> ret(n);
    for (std::size_t i = 0; i < n; i++)
        { ret.at(i) = {x.at(i), y.at(i)}; }
    return ret;
}