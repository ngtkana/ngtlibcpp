#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#define loop(n) for (int ngtkana_is_genius = 0; ngtkana_is_genius < int(n); ngtkana_is_genius++)
#define rep(i, begin, end) for(int i = int(begin); i < int(end); i++)
#define all(v) v.begin(), v.end()
#define rand(l, r) std::uniform_int_distribution<>(l, r)(mt)
using lint = long long;
auto mt = std::mt19937_64(std::random_device{}());
auto cmn = [](auto& a, auto b){if (a > b) {a = b; return true;} return false;};
auto cmx = [](auto& a, auto b){if (a < b) {a = b; return true;} return false;};
void debug_impl() { std::cerr << std::endl; }
template <typename Head, typename... Tail>
void debug_impl(Head head, Tail... tail){
  std::cerr << " " << head;
  debug_impl(tail...);
}
#ifndef STOPIT
#define debug(...)\
  std::cerr << std::boolalpha << "[" << #__VA_ARGS__ << "]:";\
  debug_impl(__VA_ARGS__);\
  std::cerr << std::noboolalpha;
#else
#define debug 0;
#endif
#include <semirings/polynominal.hpp>

#define NORMALIZE(v, x) while (!v.empty() && v.back() == x) { v.pop_back(); }

#define SUB_DIV_TEST \
  do {\
      REQUIRE(poly.sub(c, a) == poly.normalize(b));\
      REQUIRE(poly.sub(c, b) == poly.normalize(a));\
      std::vector< TestType > q, r;\
      poly.normalize(a), poly.normalize(b);\
      if (!a.empty()) {\
        std::tie(q, r) = poly.div(d, a);\
        REQUIRE(q == poly.normalize(b));\
        REQUIRE(r.empty());\
      }\
      if (!b.empty()) {\
        std::tie(q, r) = poly.div(d, b);\
        REQUIRE(q == poly.normalize(a));\
        REQUIRE(r.empty());\
      }\
    }\
  } while (false)

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


TEMPLATE_TEST_CASE( "polynominal", "[polynominal]", int, long long ) {
  auto inf = std::numeric_limits< TestType >::max();

  SECTION( "mint field" ) {
    constexpr TestType mod = 93;
    using mint = modular< std::integral_constant< TestType, mod > >;
    auto const poly = make_polynominal(
      [](auto x, auto y){ return x * y; },
      [](auto x, auto y){ return x + y; },
      mint{0},
      [](auto x, auto y){ return x / y; },
      [](auto x, auto y){ return x - y; }
    );
    auto const deg_max = 20;
    loop(72) {
      auto const k = rand(1, deg_max), l = rand(1, deg_max);
      auto const m = std::max(k, l), n = k + l - 1;
      std::vector< mint > a(k), b(l);
      for (auto & x : a) x = rand(0, mod - 1);
      for (auto & y : b) y = rand(0, mod - 1);

      // add test
      auto c = std::vector< mint >(m, 0);
      rep(i, 0, m) {
        if (i < k) c.at(i) += a.at(i);
        if (i < l) c.at(i) += b.at(i);
      }
      NORMALIZE(c, mint{0});
      REQUIRE(poly.add(a, b) == c);

      // mul test
      auto d = std::vector< mint >(n, 0);
      rep(i, 0, k) rep(j, 0, l) {
        d.at(i + j) += a.at(i) * b.at(j);
      }
      NORMALIZE(d, 0);
      REQUIRE(poly.mul(a, b) == d);

      // sub_test
      REQUIRE(poly.sub(c, a) == poly.normalize(b));
      REQUIRE(poly.sub(c, b) == poly.normalize(a));

      // div_test
      // std::vector< mint > q, r;
      // poly.normalize(a), poly.normalize(b);
      // if (!a.empty()) {
      //   std::tie(q, r) = poly.div(d, a);
      //   REQUIRE(q == poly.normalize(b));
      //   REQUIRE(r.empty());
      // }
      // if (!b.empty()) {
      //   std::tie(q, r) = poly.div(d, b);
      //   REQUIRE(q == poly.normalize(a));
      //   REQUIRE(r.empty());
      // }
    }
  }

  SECTION( "int ring (and secure division)" ) {
    auto const poly = make_polynominal(
      [](auto x, auto y){ return x * y; },
      [](auto x, auto y){ return x + y; },
      TestType{0},
      [](auto x, auto y){ return x / y; },
      [](auto x, auto y){ return x - y; }
    );
    auto const deg_max = 20;
    auto const coeff_max = std::sqrt(inf) / deg_max;
    loop(72) {
      auto const k = rand(1, deg_max), l = rand(1, deg_max);
      auto const m = std::max(k, l), n = k + l - 1;
      std::vector< TestType > a(k), b(l);
      for (auto & x : a) x = rand(-coeff_max, coeff_max);
      for (auto & y : b) y = rand(-coeff_max, coeff_max);

      // add test
      auto c = std::vector< TestType >(m, 0);
      rep(i, 0, m) {
        if (i < k) c.at(i) += a.at(i);
        if (i < l) c.at(i) += b.at(i);
      }
      while (c.empty() && c.back() == TestType{0})
        { c.pop_back(); }
      NORMALIZE(c, TestType{0});
      REQUIRE(poly.add(a, b) == c);

      // mul test
      auto d = std::vector< TestType >(n, 0);
      rep(i, 0, k) rep(j, 0, l) {
        d.at(i + j) += a.at(i) * b.at(j);
      }
      NORMALIZE(d, 0);
      REQUIRE(poly.mul(a, b) == d);

      // sub_test
      REQUIRE(poly.sub(c, a) == poly.normalize(b));
      REQUIRE(poly.sub(c, b) == poly.normalize(a));

      // div_test
      std::vector< TestType > q, r;
      poly.normalize(a), poly.normalize(b);
      if (!a.empty()) {
        std::tie(q, r) = poly.div(d, a);
        REQUIRE(q == poly.normalize(b));
        REQUIRE(r.empty());
      }
      if (!b.empty()) {
        std::tie(q, r) = poly.div(d, b);
        REQUIRE(q == poly.normalize(a));
        REQUIRE(r.empty());
      }
    }
  }

  SECTION( "min-semiring, max-semiring" ) {
    auto const min_poly = make_polynominal(
      [](auto x, auto y){ return x + y; },
      [](auto x, auto y){ return std::min(x, y); },
      inf
    );
    auto const max_poly = make_polynominal(
      [](auto x, auto y){ return x + y; },
      [](auto x, auto y){ return std::max(x, y); },
      -inf
    );
    auto const deg_max = 20;
    auto const coeff_max = inf / 2;
    loop(24) {
      auto const k = rand(1, deg_max), l = rand(1, deg_max);
      auto const m = std::max(k, l), n = k + l - 1;
      std::vector< TestType > a(k), b(l);
      for (auto & x : a) x = rand(-coeff_max, coeff_max);
      for (auto & y : b) y = rand(-coeff_max, coeff_max);

      // add test
      std::vector< TestType > c(m, inf);
      std::vector< TestType > d(m, -inf);
      rep(i, 0, m) {
        if (i < k) {
          cmn(c.at(i), a.at(i));
          cmx(d.at(i), a.at(i));
        }
        if (i < l) {
          cmn(c.at(i), b.at(i));
          cmx(d.at(i), b.at(i));
        }
      }
      NORMALIZE(c, inf);
      NORMALIZE(d, inf);
      REQUIRE(min_poly.add(a, b) == c);
      REQUIRE(max_poly.add(a, b) == d);

      // mul test
      std::vector< TestType > e(n, inf);
      std::vector< TestType > f(n, -inf);
      rep(i, 0, k) rep(j, 0, l) {
        cmn(e.at(i + j), a.at(i) + b.at(j));
        cmx(f.at(i + j), a.at(i) + b.at(j));
      }
      NORMALIZE(e, inf);
      NORMALIZE(f, inf);
      REQUIRE(min_poly.mul(a, b) == e);
      REQUIRE(max_poly.mul(a, b) == f);
    }
  }

  SECTION( "gcd semiring, lcm semiring" ) {
    auto const gcd_poly = make_polynominal(
      [](auto x, auto y){ return x * y; },
      [](auto x, auto y){ return std::__gcd(x, y); },
      TestType{0}
    );
    auto const lcm_poly = make_polynominal(
      [](auto x, auto y){ return x * y; },
      [](auto x, auto y){
        auto g = std::__gcd(x, y);
        return g == 0 ? std::max(x, y) : x / g * y;
      },
      TestType{1}
    );
    auto const deg_max = 4;
    auto const coeff_max = 24;
    loop(24) {
      auto const k = rand(1, deg_max), l = rand(1, deg_max);
      auto const m = std::max(k, l), n = k + l - 1;
      std::vector< TestType > a(k), b(l);
      for (auto & x : a) x = rand(0, coeff_max);
      for (auto & y : b) y = rand(0, coeff_max);

      // lambdas
      auto gcd_eq = [](auto& x, auto y){ x = std::__gcd(x, y); };
      auto lcm_eq = [](auto& x, auto y) {
        auto const g = std::__gcd(x, y);
        x = g == 0 ? std::max(x, y) : x / g * y;
      };

      // add test
      std::vector< TestType > c(m, 0);
      std::vector< TestType > d(m, 1);
      rep(i, 0, m) {
        if (i < k) {
          gcd_eq(c.at(i), a.at(i));
          lcm_eq(d.at(i), a.at(i));
        }
        if (i < l) {
          gcd_eq(c.at(i), b.at(i));
          lcm_eq(d.at(i), b.at(i));
        }
      }
      NORMALIZE(c, TestType{0});
      NORMALIZE(d, TestType{1});
      REQUIRE(gcd_poly.add(a, b) == c);
      REQUIRE(lcm_poly.add(a, b) == d);

      // mul test
      std::vector< TestType > e(n, 0);
      std::vector< TestType > f(n, 1);
      rep(i, 0, k) rep(j, 0, l) {
        gcd_eq(e.at(i + j), a.at(i) * b.at(j));
        lcm_eq(f.at(i + j), a.at(i) * b.at(j));
      }
      NORMALIZE(e, TestType{0});
      NORMALIZE(f, TestType{1});
      REQUIRE(gcd_poly.mul(a, b) == e);
      REQUIRE(lcm_poly.mul(a, b) == f);
    }
  }

  SECTION( "and-xor ring" ) {
    auto const poly = make_polynominal(
      [](auto x, auto y){ return x & y; },
      [](auto x, auto y){ return x ^ y; },
      TestType{0}
    );
    auto const deg_max = 40;
    loop(240) {
      auto const k = rand(1, deg_max), l = rand(1, deg_max);
      std::vector< TestType > a(k), b(l);
      for (auto & x : a) x = rand(0, inf);
      for (auto & y : b) y = rand(0, inf);

      // add test
      std::vector< TestType > c(std::max(k, l), 0);
      rep(i, 0, std::max(k, l)) {
        if (i < k) { c.at(i) ^= a.at(i); }
        if (i < l) { c.at(i) ^= b.at(i); }
      }
      NORMALIZE(c, TestType{0});
      REQUIRE(poly.add(a, b) == c);

      // mul test
      std::vector< TestType > d(k + l - 1, 0);
      rep(i, 0, k) rep(j, 0, l) {
        d.at(i + j) ^= a.at(i) & b.at(j);
      }
      NORMALIZE(c, TestType{0});
      REQUIRE(poly.mul(a, b) == d);
    }
  }
}
