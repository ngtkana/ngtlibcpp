# factorials
[prev](..\index.md)
```cpp
struct factorials {
  const int sz;
  vector<int> fct, fnv;
  factorials (int n)
    : sz(n)
    , fct(n, 1)
    , fnv(n, 1)
    {
      for (int i = 1; i < n; i++) fct[i] = mul(fct[i - 1], i);
      fnv[n - 1] = inv(fct[n - 1]);
      for (int i = n - 1; i >= 1; i--) fnv[i - 1] = mul(fnv[i], i);
    }
  inline int binom (int n, int k) {
    assert(0 <= k && k <= n && n < sz);
    return mul(fct[n], mul(fnv[k], fnv[n - k]));
  }
};
```
