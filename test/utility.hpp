template <typename T, typename U>
struct minimum_function_t
{
	auto operator()(T t, U u) const {return std::min(t, u);}
};
