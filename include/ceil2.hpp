template < class Value >
Value ceil2(Value x) {
    if (x == 0 || x == 1) return 1;
    return (std::numeric_limits< Value >::max() >> __builtin_clzll(x - 1) - 1) + 1;
}
