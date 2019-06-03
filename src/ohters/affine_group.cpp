  auto apply = [&] (pair<int, int>p, int& ret) -> void {
    int coeff, a; tie(coeff, a) = p;
    mint::mul(ret, coeff);
    mint::add(ret, a);
  };
  auto cmp = [&] (pair<int, int> p, pair<int, int> q) -> pair<int, int> {
    int a, b; tie(a, b) = p;
    int c, d; tie(c, d) = q;
    return {mint::prod(a, c), mint::sum(mint::prod(a, d), b)};
  };
  auto cmp_pow = [&] (pair<int, int> p, int k) -> pair<int, int> {
    pair<int, int> ret = {1, 0};
    while (k) {
      if (k & 1) ret = cmp(ret, p);
      k /= 2;
      p = cmp(p, p);
    }
    return ret;
  };