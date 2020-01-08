template < class Value >
Value remove_bit(Value x, int j) {
  Value low = x & (Value(1) << j) - 1;
  return (x >> j + 1 << j) + low;
}
