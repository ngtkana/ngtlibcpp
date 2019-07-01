template<typename T>
class convolution {
  const T id;
  const std::function<void(T&, T)> add;
  const std::function<T(T, T)> mul;
  public:
    convolution (
        T id,
        std::function<void(T&, T)> add,
        std::function<T(T, T)> mul
      ) :
      id(id),
      add(add),
      mul(mul)
      {
      }
    auto operator () (
        std::vector<T> a,
        std::vector<T> b
      ) -> std::vector<T>
      {
        int l = a.size();
        int m = b.size();
        int n = l + m - 1;
        assert(l && m);
        std::vector<T> c(n, id);
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
  