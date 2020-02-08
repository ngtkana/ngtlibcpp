template <int N, typename Semiring>
class square_matrix
{
<tab>template <int N_, typename Semiring_>
<tab>friend bool operator==(const square_matrix<N_, Semiring_>&, const square_matrix<N_, Semiring_>&);

<tab>public:
<tab><tab>using this_type<tab> = square_matrix<N, Semiring>;
<tab><tab>using value_type<tab>= typename Semiring::type;
<tab><tab>using matrix_type = std::array<std::array<value_type, N>,<tab>N>;

<tab>private:
<tab><tab>matrix_type storage;

<tab>public:
<tab><tab>constexpr square_matrix() = default;
<tab><tab>constexpr square_matrix(const square_matrix&) = default;
<tab><tab>constexpr square_matrix(square_matrix&&) = default;
<tab><tab>square_matrix& operator=(const square_matrix&) = default;
<tab><tab>square_matrix& operator=(square_matrix&&) = default;

<tab><tab>constexpr square_matrix(const matrix_type& x) : storage(x){}
<tab><tab>constexpr square_matrix
<tab><tab>(
<tab><tab><tab>std::initializer_list<std::initializer_list<value_type>> list
<tab><tab>)
<tab><tab>{
<tab><tab><tab>int i = 0;
<tab><tab><tab>for (auto &row: list)
<tab><tab><tab>{
<tab><tab><tab><tab>int j = 0;
<tab><tab><tab><tab>for (auto val : row)
<tab><tab><tab><tab>{
<tab><tab><tab><tab><tab>storage.at(i).at(j) = val;
<tab><tab><tab><tab><tab>j++;
<tab><tab><tab><tab>}
<tab><tab><tab><tab>i++;
<tab><tab><tab>}
<tab><tab>}

<tab><tab>// Special Elements.
<tab><tab>static auto zero_matrix()
<tab><tab>{
<tab><tab><tab>auto ret = this_type{};
<tab><tab><tab>for (int i = 0; i < N; i++)
<tab><tab><tab>{
<tab><tab><tab><tab>for (int j = 0; j < N; j++)
<tab><tab><tab><tab>{
<tab><tab><tab><tab><tab>ret.at(i, j) = Semiring::add_id();
<tab><tab><tab><tab>}
<tab><tab><tab>}
<tab><tab><tab>return ret;
<tab><tab>}

<tab><tab>static auto identity_matrix()
<tab><tab>{
<tab><tab><tab>auto ret = this_type{};
<tab><tab><tab>for (int i = 0; i < N; i++)
<tab><tab><tab>{
<tab><tab><tab><tab>for (int j = 0; j < N; j++)
<tab><tab><tab><tab>{
<tab><tab><tab><tab><tab>ret.at(i, j) = i == j
<tab><tab><tab><tab><tab><tab>? Semiring::mul_id()
<tab><tab><tab><tab><tab><tab>: Semiring::add_id();
<tab><tab><tab><tab>}
<tab><tab><tab>}
<tab><tab><tab>return ret;
<tab><tab>}

<tab><tab>// Accessors.
<tab><tab>auto& at(int i, int j)<tab><tab><tab> {return storage.at(i).at(j);}
<tab><tab>auto& at(int i, int j) const {return storage.at(i).at(j);}

<tab><tab>// Operaters.
<tab><tab>auto& operator+=(const square_matrix& other)
<tab><tab>{
<tab><tab><tab>auto ret = zero_matrix();
<tab><tab><tab>for (int i = 0; i < N; i++)
<tab><tab><tab>{
<tab><tab><tab><tab>for (int j = 0; j < N; j++)
<tab><tab><tab><tab>{
<tab><tab><tab><tab><tab>Semiring::add_eq(at(i,j), other.at(i, j));
<tab><tab><tab><tab>}
<tab><tab><tab>}
<tab><tab><tab>return *this;
<tab><tab>}

<tab><tab>auto& operator*=(const square_matrix& other)
<tab><tab>{
<tab><tab><tab>auto ret = zero_matrix();
<tab><tab><tab>for (int i = 0; i < N; i++)
<tab><tab><tab>{
<tab><tab><tab><tab>for (int j = 0; j < N; j++)
<tab><tab><tab><tab>{
<tab><tab><tab><tab><tab>for (int k = 0; k < N; k++)
<tab><tab><tab><tab><tab>{
<tab><tab><tab><tab><tab><tab>Semiring::add_eq(ret.at(i, k), Semiring::mul(at(i, j), other.at(j, k)));
<tab><tab><tab><tab><tab>}
<tab><tab><tab><tab>}
<tab><tab><tab>}
<tab><tab><tab>return *this = ret;
<tab><tab>}
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
<tab>using std::literals::string_literals::operator""s;
<tab>auto ret = "square_matrix{ "s;
<tab>for (int i = 0; i < N; i++)
<tab>{
<tab><tab>if (i > 0) ret += ", ";
<tab><tab>ret += "{ ";
<tab><tab>for (int j = 0; j < N; j++)
<tab><tab>{
<tab><tab><tab>if (j > 0) ret += ", ";
<tab><tab><tab>ret += std::to_string(a.at(i, j));
<tab><tab>}
<tab><tab>ret += " }";
<tab>}
<tab>ret += " }";
<tab>return ret;
}

template <typename T>
struct min_tolopical
{
<tab>using type = T;
<tab>static auto add_id()<tab>{return std::numeric_limits<T>::max();}
<tab>static auto mul_id()<tab>{return 0;}
<tab>static auto add(T x, T y) {return std::min(x, y);}
<tab>static auto mul(T x, T y)
<tab>{
<tab><tab>if (x == add_id() || y == add_id()) return add_id();
<tab><tab>return x + y;
<tab>}
<tab>static auto add_eq(T& x, T y) {return x = add(x, y);}
};

template <typename T>
struct min_tolopical
{
<tab>using type = T;
<tab>static auto add_id()<tab>{return std::numeric_limits<T>::min();}
<tab>static auto mul_id()<tab>{return 0;}
<tab>static auto add(T x, T y) {return std::max(x, y);}
<tab>static auto mul(T x, T y)
<tab>{
<tab><tab>if (x == add_id() || y == add_id()) return add_id();
<tab><tab>return x + y;
<tab>}
<tab>static auto add_eq(T& x, T y) {return x = add(x, y);}
};

template <int N, typename T>
using min_tolopical_matrix = square_matrix<N, min_tolopical<T>>;

template <int N, typename T>
using max_tolopical_matrix = square_matrix<N, min_tolopical<T>>;
