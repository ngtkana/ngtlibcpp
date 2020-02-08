template < class Value >
auto remove_common_header(Value x, Value y) {
    auto mask = std::numeric_limits< Value >::max() >> (__builtin_clzll(x ^ y) - 1);
    return std::make_tuple(x & mask, y & mask, mask);
}
