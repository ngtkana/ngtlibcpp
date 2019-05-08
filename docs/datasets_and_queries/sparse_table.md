# sparse_table
[prev](..\index.md)
```cpp
template <typename T>
class sparse_table {
  int sz, ht;
  vector<int> dpt;
  vector<vector<T>> dat;
  const function<T(T, T)> o;
  const T id;

public:
  sparse_table (vector<T> v, function<T(T, T)> o, T id)
    : sz(v.size())
    , ht(1)
    , o(o)
    , id(id)
  {
    while ((1 << ht) <= sz) ht++;
    dpt.assign(sz + 1, 0);
    dat.assign(ht, v);
    for (int j = 2; j <= sz; j++) dpt[j] = dpt[j >> 1] + 1;
    for (int i(1), p(1); i < ht; i++, p <<= 1) {
      for (int j = 0; j < sz; j++) {
        dat[i][j] = o(dat[i - 1][j], dat[i - 1][min(j + p, sz - 1)]);
      }
    }
  }
  T find (int l, int r) {
    assert(0 <= l && l <= r && r <= sz);
    if(l == r) return id;
    int i = dpt[r - l];
    return o(dat[i][l], dat[i][r - (1 << i)]);
  }
  void print () {
    for (int i = 0; i < ht; i++) {
      for (int j = 0; j < sz; j++) {
        cout << setw(4) << dat[i][j] << (j < sz - 1 ? ' ' : '\n');
      }
    }
    cout << flush;
  }
};
```
