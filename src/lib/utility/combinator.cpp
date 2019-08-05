template<typename T>
class fixed_point : T {
  public:
    explicit constexpr fixed_point (T&& t) noexcept
      : T(std::forward<T>(t)) {}
    template<typename... Args>
    constexpr decltype(auto) operator()(Args&&... args) const
      {return T::operator()(*this, std::forward<Args>(args)...);}
};
template<typename T>
static inline constexpr decltype(auto) fix (T&& t) noexcept {
  return fixed_point<T>{std::forward<T>(t)};
}