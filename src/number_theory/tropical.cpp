template <typename T, typename F, std::enable_if_t<
    std::is_same<std::result_of_t<F(T, T)>, T>::value,
    std::nullptr_t> = nullptr>
class tropical {
    T value;
  
  public:
    using value_type = T;
    constexpr tropical()=default;
    constexpr tropical(const tropical&)=default;
    constexpr tropical(tropical&&)=default;
    tropical& operator=(const tropical&)=default;
    tropical& operator=(tropical&&)=default;

    constexpr tropical(T t) : value(t){}

    auto const& operator()() const { return value; }
    template <typename U>
    explicit operator U() const { return static_cast<U>(value); }

    auto& operator+=(const tropical& other) {
      value = F{}(value, other.value);
      return *this;
    }
    template <typename U>
    auto& operator+=(const U& other) {return *this += tropical(other); }
  
    template <typename U = T>
    auto& operator*=(const tropical& other) {
      value += other.value;
      return *this;
    }
};
template <typename T> struct is_tropical : std::false_type{};
template <typename T, typename F> struct is_tropical <tropical<T, F>> : std::true_type{};
template <typename T> constexpr bool is_tropical_v = is_tropical<T>::value;

template <typename T, std::enable_if_t<
  is_tropical_v<T>, std::nullptr_t> = nullptr>
bool operator==(const T& lhs, const T& rhs) {return lhs.value == rhs.value;}

template <typename T>
auto operator+(const T& lhs, const T& rhs)
  -> std::enable_if_t<is_tropical_v<T>, T>
  {return T(lhs) += rhs;}

template <typename T>
auto operator*(const T& lhs, const T& rhs)
  -> std::enable_if_t<is_tropical_v<T>, T>
  {return T(lhs) *= rhs;}

template <typename T, typename F>
std::string to_string(const tropical<T, F>& a)
  {return std::to_string(a());}

template <typename T, typename F>
std::ostream& operator<<(std::ostream& os, const tropical<T, F>& a)
  {return os << a();}

template <typename T, typename F>
std::istream& operator>>(std::istream& is, tropical<T, F>& a)
  {T x; is >> x; a = tropical<T, F>(x); return is;}

template <typename T>
struct min_fn_object {
  auto operator()(T a, T b) {return std::min(a, b);}
};
template <typename T>
struct max_fn_object {
  auto operator()(T a, T b) {return std::max(a, b);}
};
using min_tropical = tropical<int, min_fn_object<int>>;
using max_tropical = tropical<int, max_fn_object<int>>;
