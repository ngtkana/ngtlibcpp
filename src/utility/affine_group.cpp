  auto apply = [&] (std::pair<int, int>p, int& ret) -> void {
    int coeff, a; std::tie(coeff, a) = p;
    mint::mul(ret, coeff);
    mint::add(ret, a);
  };
  auto cmp = [&] (std::pair<int, int> p, std::pair<int, int> q) -> std::pair<int, int> {
    int a, b; std::tie(a, b) = p;
    int c, d; std::tie(c, d) = q;
    return {mint::prod(a, c), mint::sum(mint::prod(a, d), b)};
  };
  auto cmp_pow = [&] (std::pair<int, int> p, int k) -> std::pair<int, int> {
    std::pair<int, int> ret = {1, 0};
    while (k) {
      if (k & 1) ret = cmp(ret, p);
      k /= 2;
      p = cmp(p, p);
    }
    return ret;
  };