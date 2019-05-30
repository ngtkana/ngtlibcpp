class finite_field {
  const int md;
  const int sz;
  vector<int> fct, fnv;
  int inv2 = -1;
  void init () {
    if (sz) {
      fct[0] = 1;
      for (int i = 1; i < sz; i++) fct[i] = prod(fct[i - 1], i);
      fnv[sz - 1] = inv(fct[sz - 1]);
      for (int i = sz - 1; i >= 1; i--) fnv[i - 1] = prod(fnv[i], i);
    }
    inv2 = inv(2);
  }
  public :
    finite_field(
        const int md,
        const int init_factorial_size = 0,
        const int init_power_size = 0
      ) :
      md(md), sz(init_factorial_size),
      fct(sz), fnv(sz)
      {
        init();
      }
    inline void add (int& a, const int b) const {
      a += b;
      if (a >= md) a -= md;
    }
    inline void sub (int& a, const int b) const {
      a -= b;
      if (a < 0) a += md;
    }
    template<class... A> inline int sum (A... args) const {
      int ret = 0;
      for (int a : initializer_list<int>{args...}) {
        add(ret, a);
      }
      return ret;
    }
    inline int dif (int a, int b) const {
      sub(a, b);
      return a;
    }
    template<class... A> inline int prod (A... args) const {
      long long ret = 1;
      for (int a : initializer_list<int>{args...}) {
        ret *= a;
        ret %= md;
      }
      return (int)ret;
    }
    void mul (int& a, int b) const {
      a = prod(a, b);
    }
    inline int inv (int a) const {
      if (a == 2 && inv2 != -1) return inv2;
      a %= md; if (a < 0) a += md;
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
    inline int quat (int a, int b) const {
      return prod(a, inv(b));
    }
    inline void div (int& a, int b) const {
      a = quat(a, b);
    }
    inline int pow (int a, long long b) {
      int ret = 1;
      for (; b; b >>= 1) {
        if (b & 1) mul(ret, a);
        a = prod(a, a);
      }
      return ret;
    }
    inline int binom (int n, int k) const {
      assert(0 <= n && n < sz);
      if (k < 0 || n < k) return 0;
      return prod(fct[n], fnv[k], fnv[n - k]);
    }
};