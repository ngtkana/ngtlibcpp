template < typename Semiring, int Length >
class polynominal {
    using Value = typename Semiring::type;
    std::vector<Value> storage;

  public:
    constexpr polynominal()=default;
    constexpr polynominal(const polynominal&)=default;
    constexpr polynominal(polynominal&&)=default;
    polynominal& operator=(const polynominal&)=default;
    polynominal& operator=(polynominal&&)=default;

    polynominal(int n, Value val) : storage(n, val){}
    polynominal(int n) : storage(n, zero()){}
    polynominal(std::initializer_list< Value > il) : storage(il){}

    static auto id()   { return polynominal{Semiring::id()}; }
    static auto zero() { return polynominal{};               }

    auto&       at    (size_t i)       { return storage.at(i); }
    auto const& at    (size_t i) const { return storage.at(i); }
    auto        degree()         const { return storage.empty() ? -1 : (int)storage.size() - 1; }

    auto& operator*=(polynominal< Semiring, Length> const& rhs) {
      int m = degree();
      int n = rhs.degree();
      if (m == -1 || n == -1) return *this = zero();
      auto ret = std::vector<Value>(std::min(n + m + 1, Length), 0);
      for (auto i = 0; i <= m; i++) {
        for (auto j = 0; j <= n && i + j < Length; j++) {
          ret.at(i + j) += at(i) * rhs.at(j);
        }
      }
      storage.swap(ret);
      return *this;
    }

    auto&       operator()()       { return storage; }
    auto const& operator()() const { return storage; }

    template < typename Semiring_, int Length_ > friend std::ostream& operator<<(std::ostream& os, polynominal< Semiring_, Length_ > const& p);
    template < typename Semiring_, int Length_ > friend bool          operator==(polynominal< Semiring_, Length_ > p, polynominal< Semiring_, Length_ > q);
};

template < typename Semiring, int Length > bool operator==(const polynominal< Semiring, Length > lhs, const polynominal< Semiring, Length > rhs) { return polynominal< Semiring, Length >(lhs)() == rhs(); }
template < typename Semiring, int Length > bool operator==(const polynominal< Semiring, Length > lhs, const typename Semiring::Value rhs) { return lhs == polynominal< Semiring, Length >{rhs}; }
template < typename Semiring, int Length > bool operator==(const typename Semiring::Value lhs, const polynominal< Semiring, Length > rhs) { return polynominal< Semiring, Length >{lhs} == rhs; }

template < typename Semiring, int Length > auto operator*(const polynominal< Semiring, Length > lhs, const polynominal< Semiring, Length > rhs) { return polynominal< Semiring, Length >(lhs) *= rhs; }
template < typename Semiring, int Length > auto operator*(const polynominal< Semiring, Length > lhs, const typename Semiring::Value rhs) { return lhs * polynominal< Semiring, Length >{rhs}; }
template < typename Semiring, int Length > auto operator*(const typename Semiring::Value lhs, const polynominal< Semiring, Length > rhs) { return polynominal< Semiring, Length >{lhs} * rhs; }

template < typename Semiring, int Length > std::ostream& operator<<(std::ostream& os, polynominal< Semiring, Length> const& p) { return os << p(); }

struct int_semiring {
  using type = int;
  static constexpr auto id()   { return 1; }
  static constexpr auto zero() { return 0; }
};
