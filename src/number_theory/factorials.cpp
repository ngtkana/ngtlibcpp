class factorials {
    std::vector<mint> fact, finv;
  public:
    factorials(int n) : fact(n), finv(n) {
      fact.at(0) = 1;
      for (int i = 1; i < n; i++) fact.at(i) = fact.at(i - 1) * mint(i);
      finv.at(n - 1) = mint(1) / fact.at(n - 1);
      for (int i = n - 2; i >= 0; i--) finv.at(i) = finv.at(i + 1) * mint(i + 1);
    }
    // Returns the factorial.
    template <typename T>
    auto const& operator()(T i) const {return fact.at(i);}
    // Returns the inverse of the factorial.
    template <typename T>
    auto const& inv(T i) const {return finv.at(i);}
    // Returns the binominal coefficient.
    template <typename T>
    auto binom(T i, T j) const {
      assert(0 <= i);
      if (j < 0 ||i < j) return mint(0);
      return fact.at(i) * finv.at(j) * finv.at(i - j);
    }
};