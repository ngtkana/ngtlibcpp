struct rational {int n, d;};
auto to_string(rational r) -> std::string {
  return r.d == 1
    ? std::to_string(r.n)
    : std::to_string(r.n) + "/" + std::to_string(r.d);
}
std::ostream& operator << (std::ostream& os, rational r)
  { return os << to_string(r); }
auto guess (mint k) -> rational {
  auto const dmax = 1000;
  auto const nmax = 1000;
  for (auto d = 1; d < dmax; d++) {
    auto n = int(k * mint(d));
    if (n < nmax) return {n, d};
    n = mod - n;
    if (n < nmax) return {-n, d};
  }
  return {-1, 0};
}
