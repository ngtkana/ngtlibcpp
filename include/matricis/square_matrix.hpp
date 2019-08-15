template <int N, typename Semiring>
class square_matrix
{
  template <int N_, typename Semiring_>
  friend bool operator==(const square_matrix<N_, Semiring_>&, const square_matrix<N_, Semiring_>&);

  public:
    using this_type   = square_matrix<N, Semiring>;
    using value_type  = typename Semiring::type;
    using matrix_type = std::array<std::array<value_type, N>,  N>;

  private:
    matrix_type storage;

  public:
    constexpr square_matrix() = default;
    constexpr square_matrix(const square_matrix&) = default;
    constexpr square_matrix(square_matrix&&) = default;
    square_matrix& operator=(const square_matrix&) = default;
    square_matrix& operator=(square_matrix&&) = default;

    constexpr square_matrix(const matrix_type& x) : storage(x){}
    constexpr square_matrix
    (
      std::initializer_list<std::initializer_list<value_type>> list
    )
    {
      int i = 0;
      for (auto &row: list)
      {
        int j = 0;
        for (auto val : row)
        {
          storage.at(i).at(j) = val;
          j++;
        }
        i++;
      }
    }

    // Special Elements.
    static auto zero_matrix()
    {
      auto ret = this_type{};
      for (int i = 0; i < N; i++)
      {
        for (int j = 0; j < N; j++)
        {
          ret.at(i, j) = Semiring::add_id();
        }
      }
      return ret;
    }

    static auto identity_matrix()
    {
      auto ret = this_type{};
      for (int i = 0; i < N; i++)
      {
        for (int j = 0; j < N; j++)
        {
          ret.at(i, j) = i == j
            ? Semiring::mul_id()
            : Semiring::add_id();
        }
      }
      return ret;
    }

    // Accessors.
    auto& at(int i, int j)       {return storage.at(i).at(j);}
    auto& at(int i, int j) const {return storage.at(i).at(j);}

    // Operaters.
    auto& operator+=(const square_matrix& other)
    {
      auto ret = zero_matrix();
      for (int i = 0; i < N; i++)
      {
        for (int j = 0; j < N; j++)
        {
          Semiring::add_eq(at(i,j), other.at(i, j));
        }
      }
      return *this;
    }

    auto& operator*=(const square_matrix& other)
    {
      auto ret = zero_matrix();
      for (int i = 0; i < N; i++)
      {
        for (int j = 0; j < N; j++)
        {
          for (int k = 0; k < N; k++)
          {
            Semiring::add_eq(ret.at(i, k), Semiring::mul(at(i, j), other.at(j, k)));
          }
        }
      }
      return *this = ret;
    }
};

template <typename T>
struct is_square_matrix : std::false_type{};

template <int N, typename Semiring>
struct is_square_matrix<square_matrix<N, Semiring>> : std::true_type{};

template <typename T>
bool operator==(const T& lhs, const T& rhs) { return lhs.value == rhs.value; }

template <typename T>
bool operator!=(const T& lhs, const T& rhs) { return !(lhs == rhs); }

template <typename T>
T operator+(T lhs, const T& rhs) { return lhs += rhs; }

template <typename T>
T operator*(T lhs, const T& rhs) { return lhs *= rhs; }


template <int N, typename Semiring>
std::string to_string(const square_matrix<N, Semiring>& a)
{
  using std::literals::string_literals::operator""s;
  auto ret = "square_matrix{ "s;
  for (int i = 0; i < N; i++)
  {
    if (i > 0) ret += ", ";
    ret += "{ ";
    for (int j = 0; j < N; j++)
    {
      if (j > 0) ret += ", ";
      ret += std::to_string(a.at(i, j));
    }
    ret += " }";
  }
  ret += " }";
  return ret;
}

template <typename T>
struct min_tolopical
{
  using type = T;
  static auto add_id()  {return std::numeric_limits<T>::max();}
  static auto mul_id()  {return 0;}
  static auto add(T x, T y) {return std::min(x, y);}
  static auto mul(T x, T y)
  {
    if (x == add_id() || y == add_id()) return add_id();
    return x + y;
  }
  static auto add_eq(T& x, T y) {return x = add(x, y);}
};

template <typename T>
struct min_tolopical
{
  using type = T;
  static auto add_id()  {return std::numeric_limits<T>::min();}
  static auto mul_id()  {return 0;}
  static auto add(T x, T y) {return std::max(x, y);}
  static auto mul(T x, T y)
  {
    if (x == add_id() || y == add_id()) return add_id();
    return x + y;
  }
  static auto add_eq(T& x, T y) {return x = add(x, y);}
};

template <int N, typename T>
using min_tolopical_matrix = square_matrix<N, min_tolopical<T>>;

template <int N, typename T>
using max_tolopical_matrix = square_matrix<N, min_tolopical<T>>;
