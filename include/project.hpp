template < std::size_t I, typename Container,
    typename Value = typename std::tuple_element_t< I, typename Container::value_type >>
inline auto project(Container const& v) {
    std::vector< Value > ret(v.size());
    std::transform(v.begin(), v.end(), ret.begin(), [](auto&& t){ return std::get< I >(t); });
    return ret;
}
