class rolling_hash {
  public:
    using value_type     = long long;
    using container_type = std::vector<value_type>;

  private:
    static constexpr size_t  mod_num = 2;
    static constexpr std::array<value_type, mod_num> mods = {
        1'000'000'007,
        1'000'000'009
      };
    static constexpr value_type base    = 9973;

    size_t                       n;
    std::vector<container_type>  hash_table;
    std::vector<container_type>  pow_table;

    auto inverse(value_type a, value_type m) const -> value_type {
      value_type u = 0, v = 1;
      while (a != 0) {
        value_type t = m / a;
        m -= t * a; std::swap(a, m);
        u -= t * v; std::swap(u, v);
      }
      assert(m == 1);
      return u;
    }

  public:
    // ctor, dtor
    explicit rolling_hash() = default;
    explicit rolling_hash(const rolling_hash&) = default;
    explicit rolling_hash(rolling_hash&&) = default;
    rolling_hash& operator=(const rolling_hash&) = default;
    rolling_hash& operator=(rolling_hash&&) = default;
    ~rolling_hash() = default;

    rolling_hash(const std::string s) :
      n(s.length()),
      hash_table(mod_num, container_type(n + 1, 0)),
      pow_table (mod_num, container_type(n + 1, 1))
      {
        for (size_t i = 0; i < mod_num; i++) {
          auto  mod = mods.at(i);
          auto& tab = hash_table.at(i);
          auto& pab = pow_table.at(i);
          for (size_t j = 0; j < n; j++) {
            tab.at(j + 1) = (tab.at(j) * base + s.at(j)) % mod;
            pab.at(j + 1) = (pab.at(j) * base) % mod;
          }
        }
      }

    // observers
    auto hash(size_t l, size_t r) const {
      auto ret = std::vector<value_type>{};
      for (size_t i = 0; i < mod_num; i++) {
        const auto  mod = mods.at(i);
        const auto& tab = hash_table.at(i);
        const auto& pab = pow_table.at(i);
        auto &      buf = ret.at(i);
        buf = (tab.at(r) - tab.at(l)) * inverse(pab.at(l), mod) % mod;
      }
      return ret;
    }
};