template <typename... Args, std::size_t ... Inds>
std::ostream& tuple_output_impl(
  std::ostream& os,
  const std::tuple<Args...>& tuple,
  std::integer_sequence<std::size_t, Inds...>
)
{
  os << "(";
  (void)std::initializer_list<int>{(
    (void)(os << (Inds > 0 ? "," : "") << std::get<Inds>(tuple)), 0
  )...};
  return os << ")";
}
template <typename... Args>
std::ostream& operator<< (std::ostream& os, const std::tuple<Args...>& tuple)
 { return tuple_output_impl(os, tuple, std::index_sequence_for<Args...>()); }

template <typename... Args, std::size_t ... Inds>
std::istream& tuple_input_impl(
  std::istream& is,
  std::tuple<Args...>& tuple,
  std::integer_sequence<std::size_t, Inds...>
)
{
  (void)std::initializer_list<int>{(
    (void)(is >> std::get<Inds>(tuple)), 0
  )...};
  return is;
}
template <typename... Args>
std::istream& operator>> (std::istream& is, std::tuple<Args...>& tuple)
  { return tuple_input_impl(is, tuple, std::index_sequence_for<Args...>()); }
