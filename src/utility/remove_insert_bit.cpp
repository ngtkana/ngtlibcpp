  // Remove the j-th bit of x, then shift the upper part to the right.
  auto remove_bit = [](unsigned x, size_t j) -> unsigned {
    return ((x >> (j + 1)) << j) + (x & ((1 << j) - 1));
  };
  // Insert the bit b to x.at(j), shifting the upper part to the left.
  auto insert_bit = [](unsigned x, size_t j, bool b) -> unsigned {
    return ((x >> j) << (j + 1)) + (b << j) + (x & ((1 << j) - 1));
  };