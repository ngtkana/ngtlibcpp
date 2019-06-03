struct rational {int n, d;};
ostream& operator << (ostream& os, rational r){
  if (r.d == 1) {
    os << r.n;
  } else {
    os << r.n << "/" << r.d;
  }
  return os;
}
rational guess (int k) {
  const int dmx = 1000;
  const int nmx = 1000;
  for (int d = 1; d < dmx; d++) {
    int n = mint::prod(k, d);
    if (n < nmx) {
      return {n, d};
    }
  }
  return {-1, -1};
}