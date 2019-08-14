constexpr int inf = std::numeric_limits<int>::max();

template <typename T>
struct minimum_function_t
{
	auto operator()(T x, T y) const {return std::min(x, y);}
};

const auto min_fn    = [](auto x, auto y){return std::min(x, y);};
const auto sum_fn    = [](auto x, auto y){return x + y;};
const auto dif_fn    = [](auto x, auto y){return x - y;};
const auto update_fn = [](auto x, auto y){return y == -1 ? x : y;};
const auto id_fn     = [](auto x)        {return x;};
const auto twice_fn  = [](auto x)        {return x == -1 ? -1 : 2 * x;};
const auto half_fn   = [](auto x)        {return x == -1 ? -1 : x / 2;};

using min_fn_t    = decltype(min_fn);
using sum_fn_t    = decltype(sum_fn);
using dif_fn_t    = decltype(dif_fn);
using update_fn_t = decltype(update_fn);
using id_fn_t     = decltype(id_fn);
using twice_fn_t  = decltype(twice_fn);
using half_fn_t   = decltype(half_fn);
