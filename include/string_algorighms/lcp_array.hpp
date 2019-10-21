class suffix_array {
    int                n;
    std::string        s;
    std::vector< int > suf;
    std::vector< int > rank;
    std::vector< int > lcp;

  public:
    suffix_array()=default;
    suffix_array(const std::string& s) :
      n(s.length()), s(s), suf(n), rank(n), lcp(n) {}

    void build() {
      suf.resize(n, 0);
      rank.resize(n, 0);
      std::iota(suf.begin(), suf.end(), 0);
      for (auto i = 0; i < n; i++)
        { rank.at(i) = s.at(i); }
      auto comb = 1;
      auto cmp = [&](auto i, auto j) {
        if (rank.at(i) < rank.at(j)) return true;
        if (rank.at(i) > rank.at(j)) return false;
        if (n <= i + comb) return true;
        if (n <= j + comb) return false;
        return rank.at(i + comb) < rank.at(j + comb);
      };
      std::vector< int > buff(n);
      for (; comb < n; comb *= 2) {
        std::sort(suf.begin(), suf.end(), cmp);
        buff.at(suf.front()) = 0;
        for (auto i = 1; i < n; i++) {
          buff.at(suf.at(i)) = buff.at(suf.at(i - 1)) + cmp(suf.at(i - 1), suf.at(i));
        }
        buff.swap(rank);
      }
      for (auto i = 0; i < n; i++)
        { rank.at(suf.at(i)) = i; }

      auto now = 0;
      for (auto i = 0; i < n; i++) {
        auto x = rank.at(i);
        if (x == n - 1) continue;
        auto y = x + 1;
        auto j = suf.at(y);
        if (0 < now) now--;
        for (; now + std::max(i, j) < n; now++) {
          if (s.at(i + now) != s.at(j + now))
            { break; }
        }
        lcp.at(x) = now;
      }
    }

    auto get_suf() const { return suf; }
    auto get_lcp() const { return lcp; }
};
