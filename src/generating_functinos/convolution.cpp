template<typename T>
class convolution {
  function<void(T&, T)> add;
  function<T(T, T)> mul;
  public:
    convolution (
        function<void(T&, T)> add,
        function<T(T, T)> mul
      ) :
      add(add),
      mul(mul)
      {
      }
    auto operator () (
        vector<T> a,
        vector<T> b
      ) -> vector<T>
      {
        int l = a.size();
        int m = b.size();
        int n = l + m - 1;
        assert(l && m);
        vector<T> c(n, 0);
        for (int i = 0; i < l; i++) {
          for (int j = 0; j < m; j++) {
            add(c[i + j], mul(a[i], b[j]));
          }
        }
        return c;
      }
};