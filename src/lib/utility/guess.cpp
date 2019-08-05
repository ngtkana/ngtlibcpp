struct rational {int n, d;};
auto to_string(rational r) -> std::string {
  return (r.d == 1
    ? std::to_string(r.n)
    : std::to_string(r.n) + "/" + std::to_string(r.d));
}
std::ostream& operator << (std::ostream& os, rational r){
  return os << to_string(r);
}
rational guess (mint k) {
  const int dmx = 1000;
  const int nmx = 1000;
  for (int d = 1; d < dmx; d++) {
    int n = int(k * mint(d));
    if (n < nmx) return {n, d};
  }
  return {-1, 0};
}
