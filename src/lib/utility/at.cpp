  // Access the j-th bit.
  auto at = [](unsigned x, size_t j) -> bool {
    return (x >> j) & 1;
  };