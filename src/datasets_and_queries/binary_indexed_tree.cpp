template <typename T>
class binary_indexed_tree {
    size_t sz;
    vector<T> tr;
    function<T(T, T)> sum;
    function<T(T, T)> dif;
    T id;
  public:
    binary_indexed_tree (
        size_t n,
        function<T(T, T) > sum,
        function<T(T, T) > dif,
        T id
      ) :
      sz(n), tr(n, id),
      sum(sum), dif(dif), id(id)
      {}
    auto query (size_t l, size_t r) const -> T {
      assert(0 <= l && l <= r && r <= sz);
      if (l == 0) {
        int k = (int)r;
        k--;
        T ret = 0;
        for (; k >= 0; k &= k + 1, k--) ret = sum(ret, tr[k]);
        return ret;
      }
      else
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
    void print() {
      cout << "bit: ";
      for (int i = 0; i < sz; i++) {
        if (i) cout << " ";
        cout << operator[](i);
      }
      cout << endl;
    }
};