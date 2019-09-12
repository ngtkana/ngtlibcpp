class fully_indexable_dictionary {
    int                   n, blk;
    std::vector<unsigned> data;
    std::vector<int>      cum;

    auto quat(int i) const { return i / 32; }
    auto res (int i) const { return i % 32; }
    bool bat  (unsigned  x, int i) const { return (x >> i) & 1u; }
    auto bit_set (unsigned& x, int i) const { return x |= (1u << i); }

  public:
    fully_indexable_dictionary()=default;
    fully_indexable_dictionary(int n):
      n     (n),
      blk   (n / 32 + 1),
      data  (blk, 0),
      cum   (blk)
      {}

    auto size()      const { return n; }
    bool at  (int i) const { return bat (data.at(quat(i)), res(i)); }
    void set (int i)       {        bit_set(data.at(quat(i)), res(i)); }

    void build() {
      cum.at(0) = 0;
      for (auto i = 0; i < blk - 1; i++)
        { cum.at(i + 1) = cum.at(i) + __builtin_popcount(data.at(i)); }
    }

    auto rank(int k) const {
      return cum.at(quat(k))
        + __builtin_popcount(data.at(quat(k)) & ((1u << res(k)) - 1));
    }
    auto rank(int k, bool x) const
      { return x ? rank(k) : k - rank(k); }

    auto select(int k, bool x) const {
      assert(0 <= k);
      auto lwr = 0, upr = n + 1;
      while (lwr + 1 < upr) {
        auto mid = (lwr + upr) / 2;
        (rank(mid, x) <= k ? lwr : upr) = mid;
      }
      return lwr;
    }
    auto select(int k, bool x, int offset) const
      { return select(x, k + rank(x, offset)); }
};

std::ostream& operator<<(std::ostream& os, fully_indexable_dictionary const& v) {
  auto n = v.size();
  os << "{";
  for (auto i = 0; i < n; i++)
    { os << (i > 0 ? "," : "") << std::noboolalpha << v.at(i); }
  return os << "}";
}

template < typename Value  >
class wavelet_matrix  {
    using dict = fully_indexable_dictionary;

    int                 h;
    int                 w;
    std::vector< dict > tab;
    std::vector< int  > zs;
    std::vector< int  > buf0;
    std::vector< int  > buf1;

    auto bat (int x, int j) -> bool {return (x >> j) & 1;}

    auto rangefreq_impl(int i, int l, int r, Value min, Value max, Value lwr, Value upr) {
      if (l == r) { return 0;}
      if (i == h) { return (lwr <= min && min < upr) ? r - l : 0;}
      auto mid = min + (max - min) / 2;
      if (max < lwr || upr <= min) return 0;
      if (lwr <= min && max < upr) return r - l;
      auto lc = tab.at(i).rank(l, 1);
      auto rc = tab.at(i).rank(r, 1);
      return
          rangefreq_impl(i + 1,        l - lc,        r - rc, min, mid, lwr, upr)
        + rangefreq_impl(i + 1, lc + zs.at(i), rc + zs.at(i), mid, max, lwr, upr);
    }

  public:
    wavelet_matrix()=default;
    wavelet_matrix(std::vector< Value > v, int const h):
      h   (h),
      w   (v.size()),
      tab (h, dict(w)),
      zs  (h),
      buf0(h),
      buf1(h)
    {
      std::vector< Value > l(w), r(w);
      for (auto i = 0; i < h; i++) {
        auto& row = tab.at(i);
        int p = 0, q = 0;
        for (auto j = 0; j < w; j++) {
          auto crr = v.at(j);
          if (bat(crr, h - 1 - i)) {
            r.at(q++) = crr;
            row.set(j);
          } else {
            l.at(p++) = crr;
          }
        }
        row.build();
        zs.at(i) = p;
        std::copy(r.begin(), r.begin() + q, l.begin() + p);
        std::swap(l, v);
      }
    }

    auto access(int k) const {
      Value ret = 0;
      for (auto i = 0; i < h; i++) {
        auto& row = tab.at(i);
        auto const upr = row.at(k);
        ret = (ret << 1) | upr;
        k = row.rank(k, upr) + zs.at(i) * upr;
      }
      return ret;
    }
    auto at(int k) const { return access(k); }

    auto rank(int l, int r, Value x) {
      for (auto i = 0; i < h; i++) {
        auto upr = bat(x, h - i - 1);
        l = tab.at(i).rank(l, upr) + zs.at(i) * upr;
        r = tab.at(i).rank(r, upr) + zs.at(i) * upr;
      }
      return r - l;
    }

    auto select(int k, Value x) {
      rank(0, w, x);
      for (auto i = h - 1; i >= 0; i--) {
        auto upr = bat(x, h - 1 - i);
        k = tab.at(i).select(k, upr, buf0.at(i));
        if (k < 0 || buf1.at(i) <= k) return w;
        k -= buf0.at(i);
      }
      return k;
    }
    auto select(int k, Value x, int offset)
      { return select(k + rank(0, offset, x), x); }

    auto quantile(int l, int r, int k) {
      assert(0 <= k && k <= r - l);
      Value ret = 0;
      for (auto i = 0; i < h; i++) {
        auto p = tab.at(i).rank(l, true);
        auto q = tab.at(i).rank(r, true);
        if (k < q - p) {
          l = p + zs.at(i);
          r = q + zs.at(i);
          ret |= Value(1) << (h - 1 - i);
        } else {
          k -= (q - p);
          l -= p;
          r -= q;
        }
      }
      return ret;
    }
    auto rquantile(int l, int r, int k)
      { return quantile(l, r, r - l - 1 - k); }

    auto rangefreq(int l, int r, Value lwr, Value upr)
      { return rangefreq_impl(0, l, r, 0, Value(1) << h, lwr, upr); }
};