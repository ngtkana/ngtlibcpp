constexpr int md = ${1:1e9 + 7};
inline void add(int &a, int b) {
  a += b;
  if (a >= md) a -= md;
}
inline void sub(int &a, int b) {
  a -= b;
  if (a < 0) a += md;
}
inline int mul(int a, int b) {
  return (int)((long long)a * b % md);
}
inline int power(int a, long long b) {
  int res = 1;
  while (b > 0) {
    if (b & 1) {
      res = mul(res, a);
      b--;
    }
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}
inline int inv(int a) {
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
