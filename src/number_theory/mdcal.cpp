constexpr int md = ${1:1e9 + 7};
inline void mad (int &a, int b) {
  a += b; if (a >= md) a -= md;
}
inline void msb (int &a, int b) {
  a -= b; if (a < 0) a += md;
}
inline int vad (int a, int b) {
  mad(a, b); return a;
}
inline int vsb (int a, int b) {
  msb(a, b); return a;
}
inline int mul (int a, int b) {
  return (int)((long long)a * b % md);
}
inline int mow (int a, long long b) {
  int res = 1;
  for (; b; b >>= 1) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
  }
  return res;
}
inline int inv (int a) {
  a %= md;
  if(a < 0) a += md;
  int b = md, u = 0, v = 1;
  while (a) {
    int t = b / a;
    b -= a * t; swap(a, b);
    u -= v * t; swap(u, v);
  }
  assert(b == 1);
  if(u < 0) u += md;
  return u;
}
