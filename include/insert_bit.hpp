template < class Value >
Value insert_bit(Value x, int j, bool bit) {
    Value low = x & (Value(1) << j) - 1;
    return (x >> j << j + 1) + (Value(bit) << j) + low;
}
