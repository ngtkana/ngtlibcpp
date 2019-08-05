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