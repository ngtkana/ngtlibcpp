struct rational {int n, d;};
ostream& operator << (ostream& os, rational r){
  os << r.n << "/" << r.d;
  return os;
}
rational guess (int k) {
  const int dmx = 1000;
  const int nmx = 1000;
  for (int d = 1; d < dmx; d++) {
    int n = mint::prod(k, d);
    if (gcd(n, d) == 1 && n < nmx) {
      return {n, d};
    }
  }
  return {-1, -1};
}