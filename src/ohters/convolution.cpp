template<typename T>
class convolution {
  const T id;
  const function<void(T&, T)> add;
  const function<T(T, T)> mul;
  public:
    convolution (
        T id,
        function<void(T&, T)> add,
        function<T(T, T)> mul
      ) :
      id(id),
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
        vector<T> c(n, id);
        for (int i = 0; i < l; i++) {
          for (int j = 0; j < m; j++) {
            add(c[i + j], mul(a[i], b[j]));
          }
        }
        return c;
      }
};
convolution<${1:long long}> cnv(
    ${2:id},
    ${3:add},
    ${4:mul}
  );
  