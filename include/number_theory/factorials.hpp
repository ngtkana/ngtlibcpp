
class factorials
{
    std::vector<mint> fact, finv;

  public:
    factorials()=default;

    void build(int n)
    {
      fact.resize(n), finv.resize(n);
      fact.at(0) = 1;
      for (int i = 1; i < n; i++) fact.at(i) = fact.at(i - 1) * mint(i);
      finv.at(n - 1) = mint(1) / fact.at(n - 1);
      for (int i = n - 2; i >= 0; i--) finv.at(i) = finv.at(i + 1) * mint(i + 1);
    }

    // Factorial.
    auto operator()(int i) const {return fact.at(i);}

    // Inverse of Facgorial.
    auto inv       (int i) const {return finv.at(i);}

    // Binominal Coefficient.
    auto binom(int i, int j) const
    {
      assert(0 <= i);
      if (j < 0 ||i < j) return mint(0);
      return fact.at(i) * finv.at(j) * finv.at(i - j);
    }

    // Deal Apples.
    auto deal(int i, int j) const
    {
      return binom(i + j - 1, j - 1);
    }
};