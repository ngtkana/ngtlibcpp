template <typename T>
T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T t = m / a;
    m -= t * a; std::swap(a, m);
    u -= t * v; std::swap(u, v);
  }
  assert(m == 1);
  return u;
}
template <typename T>
class modular {
  private:
    int value;
  public:
    constexpr modular() = default;
    constexpr modular(const modular&) = default;
    constexpr modular(modular&&) = default;
    modular& operator=(const modular&) = default;
    modular& operator=(modular&&) = default;

    template <typename U>
    modular (const U& x) {value = normalize(x);}

    template <typename U>
    static auto normalize(const U& x) {
      int v = static_cast<int>(-mod() <= x && x < mod() ? x : x % mod());
      if (v < 0) v += mod();
      return v;
    }

    auto const& operator()() const { return value; }
    template <typename U>
    explicit operator U() const { return static_cast<U>(value); }
    constexpr static auto mod() { return T::value; }

    auto& operator+=(const modular& other) {
      if ((value += other.value) >= mod()) value -= mod();
      return *this;
    }
    auto& operator-=(const modular& other) {
      if ((value -= other.value) < 0) value += mod();
      return *this;
    }
    template <typename U>
    auto& operator+=(const U& other) {return *this += modular(other); }
    template <typename U>
    auto& operator-=(const U& other) {return *this -= modular(other); }
    auto operator-() const { return modular(-value); }
    auto& operator++() {return *this += 1;}
    auto& operator--() {return *this -= 1;}
    auto  operator++(int) {modular result(*this); operator++(); return result;}
    auto  operator--(int) {modular result(*this); operator--(); return result;}

    template <typename U = T>
    auto& operator*=(const modular& rhs) {
      value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
      return *this;
    }
    auto& operator/=(const modular& other) {
      return *this *= modular(inverse(other.value, mod()));
    }
};
template <typename T> struct is_modular : std::false_type {};
template <typename T> struct is_modular <modular<T>> : std::true_type{};
template <typename T> constexpr bool is_modular_v = is_modular<T>::value;

template <typename T> bool operator==(const modular<T>& lhs, const modular<T>& rhs) { return lhs() == rhs(); }
template <typename T, typename U> bool operator==(const modular<T>& lhs, U rhs) { return lhs == modular<T>(rhs); }
template <typename T, typename U> bool operator==(U lhs, const modular<T>& rhs) { return modular<T>(lhs) == rhs; }

template <typename T> bool operator!=(const modular<T>& lhs, const modular<T>& rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(const modular<T>& lhs, U rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(U lhs, const modular<T>& rhs) { return !(lhs == rhs); }

template <typename T> modular<T> operator+(const modular<T>& lhs, const modular<T>& rhs) { return modular<T>(lhs) += rhs; }
template <typename T, typename U> modular<T> operator+(const modular<T>& lhs, U rhs) { return modular<T>(lhs) += rhs; }
template <typename T, typename U> modular<T> operator+(U lhs, const modular<T>& rhs) { return modular<T>(lhs) += rhs; }

template <typename T> modular<T> operator-(const modular<T>& lhs, const modular<T>& rhs) { return modular<T>(lhs) -= rhs; }
template <typename T, typename U> modular<T> operator-(const modular<T>& lhs, U rhs) { return modular<T>(lhs) -= rhs; }
template <typename T, typename U> modular<T> operator-(U lhs, const modular<T>& rhs) { return modular<T>(lhs) -= rhs; }

template <typename T> modular<T> operator*(const modular<T>& lhs, const modular<T>& rhs) { return modular<T>(lhs) *= rhs; }
template <typename T, typename U> modular<T> operator*(const modular<T>& lhs, U rhs) { return modular<T>(lhs) *= rhs; }
template <typename T, typename U> modular<T> operator*(U lhs, const modular<T>& rhs) { return modular<T>(lhs) *= rhs; }

template <typename T> modular<T> operator/(const modular<T>& lhs, const modular<T>& rhs) { return modular<T>(lhs) /= rhs; }
template <typename T, typename U> modular<T> operator/(const modular<T>& lhs, U rhs) { return modular<T>(lhs) /= rhs; }
template <typename T, typename U> modular<T> operator/(U lhs, const modular<T>& rhs) { return modular<T>(lhs) /= rhs; }

template<typename T, typename U>
modular<T> power (const modular<T>& a, U b) {
  assert(b >= 0);
  modular<T> x = a, ret = 1;
  for (; b > 0; b /= 2) {
    if (b % 2 == 1) ret *= x;
    x *= x;
  }
  return ret;
}

template <typename T>
std::string to_string(const modular<T>& a) {
  return std::to_string(a());
}
template <typename T>
auto operator<<(std::ostream& os, const T& a)
  -> std::enable_if_t<is_modular_v<T>, std::ostream&>{
    return os << a();
  }
template <typename T>
auto operator>>(std::istream& is, T& a)
  -> std::enable_if_t<is_modular_v<T>, std::istream&> {
  long long x; is >> x;
  a = T(x);
  return is;
}

using mod_type = int;

// struct variable_mod { static mod_type value; };
// mod_type variable_mod::value;
// mod_type& mod = variable_mod::value;
// using mint = modular< variable_mod >;

// constexpr int mod = 1'000'000'007;
// using mint = modular<std::integral_constant<std::decay_t<decltype(mod)>, mod>>;
