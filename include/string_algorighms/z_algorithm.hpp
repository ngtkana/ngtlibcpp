#define LOCAL
using std::to_string;
auto to_string(std::string s) -> std::string {
  return '"' + s + '"';
}
auto to_string(char c) -> std::string {
  return "'" + std::string{c} + "'";
}
auto to_string(const char* s) -> std::string {
  return to_string((std::string) s);
}
auto to_string(bool b) -> std::string {
  return (b ? "true" : "false");
}
template <typename T, typename U>
auto to_string(std::pair<T, U> p) -> std::string {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}
template <size_t N>
auto to_string(std::bitset<N> bs) -> std::string {
  std::string res{};
  for (size_t i = 0; i < N; i++)
    res.insert(res.begin(), bs.test(i) ? '1' : '0');
  return res;
}
template <typename T>
auto to_string(T v) -> std::string {
  bool flg = false;
  std::string res = "{";
  for (auto const&x : v) {
    if (flg) res += ", ";
    else flg = true;
    res += to_string(x);
  }
  res += "}";
  return res;
}
void debug_out() { std::cerr << std::endl; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  std::cerr << " " << to_string(H);
  debug_out(T...);
}
#ifdef LOCAL
#define debug(...) std::cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

auto make_z_array(std::string s) -> std::vector<int> {
  if (s.empty()) return {};
  int n = s.length();
  std::vector<int> ret(n);
  ret.at(0) = n;
  int i = 1, j = 0;
  while (i < n) {
    while (i + j < n && s.at(j) == s.at(i + j)) {
      j++;
    }
    ret.at(i) = j;
    if (j == 0) {
      i++;
    }
    else {
      int k = 1;
      while (i + k < n && k + ret.at(k) < j) {
        ret.at(i + k) = ret.at(k);
        k++;
      }
      i += k, j -= k;
    }
  }
  return ret;
}

// Returns turns all the occurence of w in s.
auto z_search(std::string w, std::string s, char dammy = '$') -> std::vector<int> {
  if (s.empty()) return {};
  assert(!w.empty());
  int m = w.length(), n = s.length();
  assert(std::find(w.begin(), w.end(), dammy) == w.end());
  assert(std::find(s.begin(), s.end(), dammy) == s.end());
  auto long_string = w + '$' + s;
  auto z_array = make_z_array(std::move(long_string));
  std::vector<int> ret;
  for (int i = 0; i < n; i++) {
    if (z_array.at(m + 1 + i) == m) {
      ret.push_back(i);
    }
  }
  return ret;
}