constexpr size_t sz = 3;
using vec = std::array<mint, sz>;
using mat = std::array<vec, sz>;
auto prod = [&] (const mat& a, const mat& b) {
  mat c{};
  for (size_t i = 0; i < sz; i++) {
    for (size_t j = 0; j < sz; j++) {
      for (size_t k = 0; k < sz; k++) {
        c.at(i).at(j) += a.at(i).at(k) * b.at(k).at(j);
      }
    }
  }
  return c;
};
auto id = [&] {
  mat c{};
  for (size_t i = 0; i < sz; i++) {
    c.at(i).at(i) = 1;
  }
  return c;
};
auto pow = [&] (mat a, long long b) {
  auto c = id();
  for (; b > 0; b /= 2) {
    if (b % 2 == 1) c = prod(c, a);
    a = prod(a, a);
  }
  return c;
};
auto act = [&] (mat a, vec b) {
  vec c{};
  for (size_t i = 0; i < sz; i++) {
    for (size_t j = 0; j < sz; j++) {
      c.at(i) += a.at(i).at(j) * b.at(j);
    }
  }
  return c;
};