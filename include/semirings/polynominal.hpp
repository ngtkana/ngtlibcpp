template < class Mul, class Add, class Value >
class polynominal {
    using poly_type = std::vector< Value >;
    Mul mul_fn;
    Add add_fn;
    Value zero;
    auto add_eq(Value & x, Value y) const { x = add_fn(x, y); }

  public:
    polynominal()=default;
    polynominal(Mul&& mul_fn, Add&& add_fn, Value zero) :
      mul_fn(std::forward< Mul >(mul_fn)),
      add_fn(std::forward< Add >(add_fn)),
      zero(zero){}

    auto add(poly_type const & a , poly_type const & b) const {
      int l = a.size(), m = b.size();
      int n = std::max(a.size(), b.size());
      poly_type c(n, zero);
      for (auto i = 0; i < n; i++) {
        if (i < l) add_eq(c.at(i), a.at(i));
        if (i < m) add_eq(c.at(i), b.at(i));
      }
      return c;
    }
    auto mul(poly_type const & a, poly_type const & b) const {
      int l = a.size(), m = b.size();
      int n = l + m - 1;
      poly_type c(n, zero);
      for (auto i = 0; i < l; i++) {
        for (auto j = 0; j < m; j++) {
          add_eq(c.at(i + j), mul_fn(a.at(i), b.at(j)));
        }
      }
      return c;
    }
};
template < class Mul, class Add, class Value >
auto make_polynominal(Mul&& mul_fn, Add&& add_fn, Value zero)
  { return polynominal< Mul, Add, Value >(std::forward< Mul >(mul_fn), std::forward< Add >(add_fn), zero); }
