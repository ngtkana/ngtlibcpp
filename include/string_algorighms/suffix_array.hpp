class suffix_array
{
  private:
    int              n;
    std::string      s;
    std::vector<int> suf;
    std::vector<int> suf_inverse;
    std::vector<int> lcp;

    template <typename T>
    auto compress(const T& v)
      -> std::vector<int>
    {
      int n = v.size();
      auto ord = std::vector<int>(n);
      std::iota(ord.begin(), ord.end(), 0);
      std::sort(ord.begin(), ord.end(), [&](auto i, auto j)
      {
        return v.at(i) < v.at(j);
      });
      auto c = std::vector<int>(n);
      int classes = 0;
      for (auto it = ord.begin(); it != ord.end(); it++)
      {
        if (it != ord.begin() && v.at(*it) != v.at(*std::prev(it)))
        {
          classes++;
        }
        c.at(*it) = classes;
      }
      return c;
    }

  public:
    suffix_array()=default;
    suffix_array(const suffix_array&)=default;
    suffix_array(suffix_array&&)=default;
    suffix_array& operator=(const suffix_array&)=default;
    suffix_array& operator=(suffix_array&&)=default;

    suffix_array(const std::string& s) :
      n(s.length()), s(s)
      {
        assert(s.back() == '$');
      }

    // Container Accessors.
    auto get_suffix_array() const {assert((int)suf.size() == n); return suf;}

    auto get_lcp_array()    const {assert((int)lcp.size() == n); return lcp;}

    // Builders.
    void build_suffix_array()
    {
      auto c = compress(s);
      for (int k = 1; k < n; k *= 2)
      {
        std::vector<std::pair<int, int>> pairs(n);
        for (int i = 0; i < n; i++)
        {
          pairs.at(i) = {c.at(i), c.at((i + k) % n)};
        }
        c = compress(pairs);
      }
      suf_inverse = std::move(c);
      suf.resize(n);
      for (int i = 0; i < n; i++)
      {
        suf.at(suf_inverse.at(i)) = i;
      }
    }

    void build_lcp_array()
    {
      int now = 0;
      lcp.resize(n, 0);
      for (auto i : suf_inverse)
      {
        if (i == n - 1) continue;
        auto pos = suf.at(i) + now;
        auto qos = suf.at(i + 1) + now;
        while (pos < n && qos < n && s.at(pos) == s.at(qos))
        {
          pos++, qos++, now++;
        }
        lcp.at(i) = now;
        if (now > 0) now--;
      }
    }
};