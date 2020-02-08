
template < class Add, class Mul, class Value, class Sub, class Div >
class polynominal {
        using poly_type = std::vector< Value >;
        Add add_fn;
        Mul mul_fn;
        Value zero;
        Sub sub_fn;
        Div div_fn;
        auto& add_eq(Value & x, Value y) const { return x = add_fn(x, y); }
        auto& sub_eq(Value & x, Value y) const { return x = sub_fn(x, y); }
        auto& mul_eq(Value & x, Value y) const { return x = mul_fn(x, y); }

    public:
        polynominal()=default;
        polynominal(
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

        auto& normalize(poly_type & a) const {
            while (!a.empty() && a.back() == zero)
                { a.pop_back(); }
            return a;
        }

        auto normalized(poly_type a) const {
            return normalize(a);
        }

        auto coeff(poly_type const & a, std::size_t i) const {
            return i < a.size() ? a.at(i) : zero;
        }

        auto eval(poly_type const & a, Value x) const {
            if (a.empty()) return zero;
            auto ret = a.front();
            auto p = x;
            for (auto i = 1; i < (int)a.size(); i++) {
                add_eq(ret, mul_fn(a.at(i), p));
                mul_eq(p, x);
            }
            return ret;
        }

        auto add(poly_type const & a , poly_type const & b) const {
            int l = a.size(), m = b.size();
            int n = std::max(a.size(), b.size());
            poly_type c(n, zero);
            for (auto i = 0; i < n; i++) {
                if (i < l) add_eq(c.at(i), a.at(i));
                if (i < m) add_eq(c.at(i), b.at(i));
            }
            return normalize(c);
        }
        auto mul(poly_type a, poly_type b) const {
            normalize(a), normalize(b);
            int l = a.size(), m = b.size();
            int n = l + m - 1;
            if (n <= 0) return poly_type{};
            poly_type c(n, zero);
            for (auto i = 0; i < l; i++) {
                for (auto j = 0; j < m; j++) {
                    add_eq(c.at(i + j), mul_fn(a.at(i), b.at(j)));
                }
            }
            return normalize(c);
        }
        auto sub(poly_type const & a , poly_type const & b) const {
            int l = a.size(), m = b.size();
            int n = std::max(a.size(), b.size());
            poly_type c(n, zero);
            for (auto i = 0; i < n; i++) {
                if (i < l) add_eq(c.at(i), a.at(i));
                if (i < m) sub_eq(c.at(i), b.at(i));
            }
            return normalize(c);
        }
        auto div(poly_type a, poly_type b) const {
            normalize(a), normalize(b);
            assert(!b.empty());
            int l = a.size(), m = b.size();
            if (l < m)
                { return std::make_pair(poly_type{}, a); }
            poly_type q(l - m + 1, zero);
            while (m <= l) {
                auto d = l - m;
                auto x = div_fn(a.back(), b.back());
                q.at(d) = x;
                for (auto i = 0; i < m; i++)
                    { sub_eq(a.at(i + d), x * b.at(i)); }
                normalize(a);
                assert((int)a.size() < l);
                l = a.size();
            }
            assert(a.size() < b.size());
            return std::make_pair(q, normalize(a));
        }
};
auto not_implemented = [](auto const x, auto const) {
    static_assert([]{ return false; }(), "Call to a not-implemented function." );
    return x;
};
using not_implemented_t = std::decay_t< decltype(not_implemented) >;
template < class Mul, class Add, class Value, class Sub = not_implemented_t, class Div = not_implemented_t >
auto make_polynominal(
    Add const& add_fn,
    Mul const& mul_fn,
    Value zero,
    Sub const& sub_fn = not_implemented,
    Div const& div_fn = not_implemented) {
    return polynominal< Add, Mul, Value, Sub, Div >(add_fn, mul_fn, zero, sub_fn, div_fn);
}
