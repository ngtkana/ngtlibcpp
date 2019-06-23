namespace mats {
  template <typename T, size_t N>
  class square_matrix {
      using mat_t = array<array<int, N>, N>;
      mat_t mat;
    public:
      square_matrix() = default;
      square_matrix(const square_matrix&) = default;
      square_matrix(square_matrix&&) = default;
      square_matrix& operator=(const square_matrix&) = default;
      square_matrix& operator=(square_matrix&&) = default;
      ~square_matrix() = default;
      square_matrix(initializer_list<initializer_list<int>> il)
        : mat([il]{
          mat_t mat;
          assert(il.size() == N);
          auto it = il.begin();
          for (size_t i = 0; i < N; i++, it++) {
            assert(it->size() == N);
            auto jt = it->begin();
            for (size_t j = 0; j < N; j++) {
              mat[i][j] = *jt;
            }
          }
          return mat;
        }()){}
      auto size () const {return N;}
      decltype(auto) at         (size_t i) const {return mat[i];}
      decltype(auto) at         (size_t i)       {return at(i);}
      decltype(auto) operator[] (size_t i) const {return at(i);}
      decltype(auto) operator[] (size_t i)       {return at(i);}
  };
  constexpr size_t N = 3;
  using T = int;
  T elem_0 = 0;
  T elem_1 = 1;
  function<void(T&, T)> elem_add  = mint::add;
  function<T(T, T)>     elem_prod = mint::prod<int, int>;
  using mat = array<array<int, N>, N>;
  auto zero = [&] () {
    mat zero;
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < N; j++) {
        zero[i][j] = elem_0;
      }
    }
    return zero;
  };
  auto id = [&] () {
    auto id = zero();
    for (size_t i = 0; i < N; i++) {
      id[i][i] = elem_1;
    }
    return id;
  };
  auto prod = [&] (const mat& a, const mat& b) {
    auto c = zero();
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < N; j++) {
        for (size_t k = 0; k < N; k++) {
          elem_add(c[i][k], elem_prod(a[i][j], b[j][k]));
        }
      }
    }
    return c;
  };
  auto pow = [&] (mat a, long long b) {
    auto ret = id();
    for (; b; b /= 2) {
      if (b % 2 == 1) {
        ret = prod(ret, a);
      }
      a = prod(a, a);
    }
    return ret;
  };
}