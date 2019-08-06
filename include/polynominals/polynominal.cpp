template <typename T,
  typename T::value_type zero, // TODO: not value_type, but T
  typename T::value_type one,  // TODO: not value_type, but T
  std::enable_if_t<
    is_tropical_v<T>,
  std::nullptr_t> = nullptr>
class polynominal {
  public:
    using value_type     = T;
    using container_type = std::vector<value_type>;

  private:
    container_type value;
  
  public:
    constexpr polynominal()=default;
    constexpr polynominal(const polynominal&)=default;
    constexpr polynominal(polynominal&&)=default;
    polynominal& operator=(const polynominal&)=default;
    polynominal& operator=(polynominal&&)=default;

    template <typename... Args>
    polynominal(Args... args) : value(std::forward<Args>(args)...) {}

    auto operator()(){return value;}


};

template <typename T> struct is_polynominal : std::false_type{};
template <typename T, T zero, T one> struct is_polynominal <polynominal<T, zero, one>> : std::true_type{};
template <typename T> constexpr bool is_polynominal_v = is_polynominal<T>::value;
