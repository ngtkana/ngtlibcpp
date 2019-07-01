namespace mint {
  int md;
  inline void add (int &a, int b) {
    assert(0 <= a && a < md && 0 <= b && b < md);
    a += b; if (a >= md) a -= md;
  }
  inline void sub (int &a, int b) {
    assert(0 <= a && a < md && 0 <= b && b < md);
    a -= b; if (a < 0) a += md;
  }
  inline int sum (int a, int b) {
    assert(0 <= a && a < md && 0 <= b && b < md);
    add(a, b); return a;
  }
  inline int dif (int a, int b) {
    assert(0 <= a && a < md && 0 <= b && b < md);
    sub(a, b); return a;
  }
  template<class... A>
  inline int prod (A... args) {
    long long ret = 1;
    for (int a :  initializer_list<int>{args...}) {
      assert(0 <= a && a < md);
      ret *= a;
      ret %= md;
    }
    return (int)(ret % md);
  }
  inline void mul (int &a, int b) {
    assert(0 <= a && a < md && 0 <= b && b < md);
    a = prod(a, b);
  }
  inline int inv (int a) {
    assert(0 <= a && a < md);
    a %= md;
    if(a < 0) a += md;
    int b = md, u = 0, v = 1;
    while (a) {
      int t = b / a;
      b -= a * t; std::swap(a, b);
      u -= v * t; std::swap(u, v);
    }
    assert(b == 1);
    if(u < 0) u += md;
    return u;
  }
  inline int quot (int a, int b) {
    assert(0 <= a && a < md && 0 <= b && b < md);
    return prod(a, inv(b));
  }
  inline void div (int& a, int b) {
    assert(0 <= a && a < md && 0 <= b && b < md);
    a = quot(a, b);
  }
  inline int pow (int a, long long b) {
    assert(0 <= a && a < md);
    int res = 1;
    for (; b; b >>= 1) {
      if (b & 1) mul(res, a);
      mul(a, a);
    }
    return res;
  }
  namespace factorials {
    int sz;
    std::vector<int> fact, finv;
    void init (int n) {
      sz = n;
      fact.resize(n); finv.resize(n);
      fact[0] = 1;
      for (int i = 1; i < n; i++) fact[i] = prod(fact[i - 1], i);
      finv[n - 1] = inv(fact[n - 1]);
      for (int i = n - 2; i >= 0; i--) finv[i] = prod(finv[i + 1], i + 1);
    }
  }
  inline int fct (int i) {
    using namespace factorials;
    assert(0 <= i && i < sz);
    return fact[i];
  }
  inline int fnv (int i) {
    using namespace factorials;
    assert(0 <= i && i < sz);
    return finv[i];
  }
  inline int binom (int n, int k) {
    using namespace factorials;
    assert(0 <= n && n < sz);
    if (0 < k || n < k) return 0;
    return prod(fact[n], finv[k], finv[n - k]);
  }
}