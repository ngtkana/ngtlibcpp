template < template < typename ... > class Tuple,    typename... Args, std::size_t ... Inds, std::size_t = std::tuple_size< Tuple < Args ... > >::value >
std::istream& tuple_input_impl(std::istream& os, Tuple<Args...>& tuple, std::integer_sequence<std::size_t, Inds...>)
    { (void)std::initializer_list<int>{((void)(os >> std::get< Inds >(tuple)), 0)...}; return os; }
template < template < typename ... > class Tuple,    typename... Args, std::size_t = std::tuple_size< Tuple < Args ... > >::value >
std::istream& operator>> (std::istream& os, Tuple<Args...>& tuple)
    { return tuple_input_impl(os, tuple, std::index_sequence_for<Args...>()); }

template < template < typename ... > class Tuple,    typename... Args, std::size_t ... Inds, std::size_t = std::tuple_size< Tuple < Args ... > >::value >
std::ostream& tuple_output_impl(std::ostream& os, const Tuple<Args...>& tuple, std::integer_sequence<std::size_t, Inds...>)
    { os << "("; (void)std::initializer_list<int>{((void)(os << (Inds > 0 ? "," : "") << std::get< Inds >(tuple)), 0)...}; return os << ")"; }
template < template < typename ... > class Tuple,    typename... Args, std::size_t = std::tuple_size< Tuple < Args ... > >::value >
std::ostream& operator<< (std::ostream& os, const Tuple<Args...>& tuple)
 { return tuple_output_impl(os, tuple, std::index_sequence_for<Args...>()); }
