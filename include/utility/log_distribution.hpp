constexpr auto inf = std::numeric_limits< TestType >::max();
auto const log_distribution = [
    impl = [](auto l, auto r) {
      assert(0 < l && l <= r);
      return TestType(std::pow(2, std::uniform_real_distribution< double >
        (std::log2(l), std::log2(r))(mt)));
    }
  ](auto l, auto r) {
    if (0 < l)  return impl(l, r);
    if (l == r) return TestType{l};
    auto const lgl = l == 0 ? 0 : std::log2(-l);
    auto const lgr = r == 0 ? 0 : std::log2(r);
    if (l == 0) return rand(0, lgr) ? impl(1, r) : TestType{0};
    if (r == 0) return rand(0, lgl) ? -impl(1, -l) : TestType{0};
    auto const lg = lgl + lgr + 1;
    auto const t = rand(0, lg - 1);
    if (t < lgl) { return -impl(1, -l); }
    if (t < lgl + lgr) { return impl(1, r); }
    return TestType{0};
};
