namespace mint {
  constexpr int md = 1e9 + 7;
  inline void add (int &a, int b) {
    a += b; if (a >= md) a -= md;
  }
  inline void sub (int &a, int b) {
    a -= b; if (a < 0) a += md;
  }
  inline int sum (int a, int b) {
    add(a, b); return a;
  }
  inline int dif (int a, int b) {
    sub(a, b); return a;
  }
  template<class... A>
  inline int prod (A... args) {
    long long ret = 1;
    for (int a : initializer_list<int>{args...}) {
      assert(a >= 0);
      ret *= a;
      ret %= md;
    }
    return (int)(ret % md);
  }
  inline void mul (int &a, int b) {
    a = prod(a, b);
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
  inline int quat (int a, int b) {
    return prod(a, inv(b));
  }
  inline void div (int& a, int b) {
    a = quat(a, b);
  }
  inline int pow (int a, long long b) {
    int res = 1;
    for (; b; b >>= 1) {
      if (b & 1) mul(res, a);
      mul(a, a);
    }
    return res;
  }
}