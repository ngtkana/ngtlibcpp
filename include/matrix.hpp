template < class Add, class Mul, class Value, class Sub, class Div >
class matrix {
        using vec_t = std::vector< Value >;
        using mat_t = std::vector< vec_t >;
        Mul mul_fn;
        Add add_fn;
        Value zero;
        Div div_fn;
        Sub sub_fn;
        auto add_eq_fn(Value & x, Value y) const { x = add_fn(x, y); }
        auto sub_eq_fn(Value & x, Value y) const { x = sub_fn(x, y); }
        auto zero_matrix(std::size_t l, std::size_t m) const
            { return mat_t(l, vec_t(m, zero)); }
     auto& at(mat_t const& a, std::size_t i, std::size_t j) const
         { return a.at(i).at(j); }
     auto& at(mat_t & a, std::size_t i, std::size_t j) const
         { return a.at(i).at(j); }

    public:
        matrix()=default;
        matrix(
            Add const& add_fn,
            Mul const& mul_fn,
            Value zero,
            Sub const& sub_fn,
            Div const& div_fn
        ) :
            add_fn(add_fn), mul_fn(mul_fn),
            zero(zero),
            sub_fn(sub_fn), div_fn(div_fn)
            {}

        auto apply(mat_t const & a, vec_t const & v) const {
            std::size_t l = a.size(), m = a.front().size();
            assert (m == v.size());
            auto ret = vec_t(l, zero);
            for (std::size_t i = 0; i < l; i++) {
                assert(a.at(i).size() == m);
                for (std::size_t j = 0; j < m; j++) {
                    add_eq_fn(ret.at(i), mul_fn(at(a, i, j), v.at(j)));
                }
            }
            return ret;
        }

        auto& add_eq(mat_t& a, mat_t const& b) const {
            std::size_t l = a.size(), m = a.front().size();
            assert(b.size() == l);
            for (std::size_t i = 0; i < l; i++) {
                assert(a.at(i).size() == m);
                assert(b.at(i).size() == m);
                for (std::size_t j = 0; j < m; j++) {
                    add_eq_fn(at(a, i, j), at(b, i, j));
                }
            }
            return a;
        }

        auto add(mat_t const& a, mat_t const& b) const {
            auto c = a;
            add_eq(c, b);
            return c;
        }

        auto mul(mat_t const& a, mat_t const& b) const {
            std::size_t l = a.size(), m = b.size(), n = b.front().size();
            auto c = zero_matrix(l, n);
            for (std::size_t i = 0; i < l; i++) {
                assert(a.at(i).size() == m);
                for (std::size_t j = 0; j < m; j++) {
                    assert(b.at(j).size() == n);
                    for (std::size_t k = 0; k < n; k++) {
                        add_eq_fn(at(c, i, k), mul_fn(at(a, i, j), at(b, j, k)));
                    }
                }
            }
            return c;
        }
};
constexpr auto not_implemented = [](auto const x, auto const) {
    static_assert([]{ return false; }(), "Call of a not-implemented function." );
    return x;
};
using not_implemented_t = std::decay_t< decltype(not_implemented) >;
template < class Mul, class Add, class Value, class Sub = not_implemented_t, class Div = not_implemented_t >
auto make_matrix(
    Add const& add_fn,
    Mul const& mul_fn,
    Value zero,
    Sub const& sub_fn = not_implemented,
    Div const& div_fn = not_implemented) {
    return matrix< Add, Mul, Value, Sub, Div >(add_fn, mul_fn, zero, sub_fn, div_fn);
}
