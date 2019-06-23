template<typename T>
class segment_tree {
  const size_t n, sz, Sz;
  vector<T> seg;
  const function<T(T, T)> o;
  const T id;
  public:
    segment_tree (
        const size_t n,
        const function<T(T, T)> o,
        const T id
      ) :
      n(n),
      sz([&](){
          size_t p = 1;
          for (; p < n; p <<= 1) {}
          return p;
        }()),
      Sz(sz << 1),
      seg(Sz, id),
      o(o),
      id(id)
      {
      }
    void update (size_t k, const T& x) {
      k += sz;
      seg[k] = x;
      while(k >>= 1) {
        seg[k] = o(seg[2 * k], seg[2 * k + 1]);
      }
    }
    void add (size_t x, const T& y) {
      update(x, at(x) + y);
    }
    T query (size_t l, size_t r) {
      T L = id, R = id;
      for(l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
        if(l & 1) L = o(L, seg[l++]);
        if(r & 1) R = o(seg[--r], R);
      }
      return o(L, R);
    }
    T at (const size_t &x) const {
      return seg[x + sz];
    }
    void print() {
      cout << setw(4) << "----"; for (size_t i = 0; i < n; i++) cout << setw(4) << "----" ; cout << endl;
      cout << setw(4) << ""; for (size_t i = 0; i < n; i++) cout << setw(4) << i; cout << endl;
      cout << setw(4) << "----"; for (size_t i = 0; i < n; i++) cout << setw(4) << "----" ; cout << endl;
      cout << setw(4) << "val"; for (size_t i = 0; i < n; i++) cout << setw(4) << seg[i + sz]; cout << endl;
      cout << setw(4) << "----"; for (size_t i = 0; i < n; i++) cout << setw(4) << "----" ; cout << endl;
    }
};