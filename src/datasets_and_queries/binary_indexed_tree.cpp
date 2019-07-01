template <typename T>
class binary_indexed_tree {
    size_t sz;
    std::vector<T> tr;
    std::function<T(T, T)> sum;
    std::function<T(T, T)> dif;
    T id;
  public:
    binary_indexed_tree (
        size_t n,
        std::function<T(T, T)> sum,
        std::function<T(T, T)> dif,
        T id
      ) :
      sz(n), tr(n, id),
      sum(sum), dif(dif), id(id)
      {}
    auto cum (size_t r) const -> T {
      assert(0 <= r && r <= sz);
      int k = (int)r;
      k--;
      T ret = 0;
      for (; k >= 0; k &= k + 1, k--) ret = sum(ret, tr[k]);
      return ret;
    }
    auto query (size_t l, size_t r) const -> T {
      assert(0 <= l && l <= r && r <= sz);
      return dif(query(0, r), query(0, l));
    }
    auto operator[] (size_t i) const -> T {
      assert(0 <= i && i < sz);
      return query(i, i + 1);
    }
    auto at (size_t i) const -> T {
      return operator[](i);
    }
    void add (size_t i, T x) {
      for (; i < sz; i |= i + 1) tr[i] = sum(tr[i], x);
    }
    void print(std::string name = "bit") {
      std::cout << name << ": ";
      for (size_t i = 0; i < sz; i++) {
        if (i) std::cout << " ";
        std::cout << operator[](i);
      }
      std::cout << std::endl;
    }
}