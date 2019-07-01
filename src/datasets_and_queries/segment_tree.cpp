template<typename T>
class segment_tree {
  const size_t n, sz, Sz;
  std::vector<T> seg;
  const std::function<T(T, T)> o;
  const T id;
  public:
    segment_tree (
        const size_t n,
        const std::function<T(T, T)> o,
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
      std::cout << std::setw(4) << "----"; for (size_t i = 0; i < n; i++) std::cout << std::setw(4) << "----" ; std::cout << std::endl;
      std::cout << std::setw(4) << ""; for (size_t i = 0; i < n; i++) std::cout << std::setw(4) << i; std::cout << std::endl;
      std::cout << std::setw(4) << "----"; for (size_t i = 0; i < n; i++) std::cout << std::setw(4) << "----" ; std::cout << std::endl;
      std::cout << std::setw(4) << "val"; for (size_t i = 0; i < n; i++) std::cout << std::setw(4) << seg[i + sz]; std::cout << std::endl;
      std::cout << std::setw(4) << "----"; for (size_t i = 0; i < n; i++) std::cout << std::setw(4) << "----" ; std::cout << std::endl;
    }
};