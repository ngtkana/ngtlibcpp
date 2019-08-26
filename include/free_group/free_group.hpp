class free_group {
  public:
  static inline auto mul(std::string s, std::string t) {
    while (
        !s.empty() && !t.empty() &&
        abs(s.back() - t.front()) == 32
      )
      {
        s.erase(s.end() - 1); t.erase(t.begin());
      }
      return s + t;
  }
  static inline auto inv (std::string s) {
    auto opp = [&] (char& c) {
        if (0 <= c - 'a' && c - 'a' < 26) c -= 32;
        else if (0 <= c - 'A' && c - 'A' < 26) c += 32;
        else assert(false);
      };
    reverse(s.begin(), s.end());
    for_each(s.begin(), s.end(), opp);
    return s;
  }
};
