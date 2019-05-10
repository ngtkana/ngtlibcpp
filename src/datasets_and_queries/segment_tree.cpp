template< typename T >
class segment_tree {
  int sz;
  vector<T> seg;
  const function<T(T, T)> o;
  const T id;
  public:
    segment_tree(int n, const function<T(T, T)> o, const T id)
      : o(o)
      , id(id)
    {
      sz = 1;
      while(sz < n) sz <<= 1;
      seg.assign(2 * sz, id);
    }
    void update(int k, const T &x) {
      k += sz;
      seg[k] = x;
      while(k >>= 1) {
        seg[k] = o(seg[2 * k], seg[2 * k + 1]);
      }
    }
    T find(int l, int r) {
      T L = id, R = id;
      for(l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
        if(l & 1) L = o(L, seg[l++]);
        if(r & 1) R = o(seg[--r], R);
      }
      return o(L, R);
    }
    T operator[](const int &k) const {
      return seg[k + sz];
    }
    void print() {
      cout << "segment_tree:" << endl;
      int crr = 1;
      for (int p = sz; p; p >>= 1) {
        for (int i = 0; i < sz; i++) {
          cout
              << setw(12)
              << (i % p == 0 ? to_string(seg[crr++]) : "")
              << (i < sz - 1 ? "" : "\n");
        }
      }
      cout << endl;
    }
};
