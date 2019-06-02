struct factorials {
  const int sz;
  const vector<int> fct, fnv;
  factorials (int n) :
    sz(n),
    fct([&](){
        vector<int> ret(n, 1);
        for (int i = 1; i < n; i++) ret[i] = mint::prod(ret[i - 1], i);
        return ret;
      }()),
    fnv([&](){
        vector<int> ret(n); ret[n - 1] = mint::inv(fct[n - 1]);
        for (int i = n - 2; i >= 0; i--) ret[i] = mint::prod(ret[i + 1], i + 1);
        return ret;
      }())
    {
    }
  inline int binom (int n, int k) {
    assert(0 <= k && k <= n && n < sz);
    return mint::prod(fct[n], fnv[k], fnv[n - k]);
  }
};