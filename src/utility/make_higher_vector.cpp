template <typename T>
auto make_vector(size_t sz, T t) {
  return std::vector<T>(sz, t);
}
template <size_t N, typename T, typename U, std::enable_if_t<
  N == 1, std::nullptr_t> = nullptr>
auto make_higher_vector(size_t sz, U u) {
  return make_vector(sz, T(u));
}
template <size_t N, typename T, std::enable_if_t<
  N == 1, std::nullptr_t> = nullptr>
auto make_higher_vector(size_t sz) {
  return std::vector<T>(sz);
}
template <size_t N, typename T, typename... Args, std::enable_if_t<
  N != 1, std::nullptr_t> = nullptr>
auto make_higher_vector(size_t a, Args... args) {
  return make_vector(a, make_higher_vector<N - 1, T>(args...));
}
template <typename T, typename Size_t>
auto& at(T& t, Size_t i) {
  return t.at(i);
}
template <typename T, typename Size_t, typename... Args>
auto& at(T& t, Size_t i, Args... args) {
  return at(t.at(i), args...);
}
