template < std::size_t N >
auto static_sieve() {
  auto is_prime = ~std::bitset< N >{};
  is_prime.reset(0);
  is_prime.reset(1);
  std::vector< int > ret;
  for (auto p = 2; p < N; p++) {
    if (!is_prime.test(p)) continue;
    ret.emplace_back(p);
    for (auto x = p * p; x < N; x += p) {
      is_prime.reset(x);
    }
  }
  return ret;
}
