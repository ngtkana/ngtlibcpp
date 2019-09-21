template < typename Container,
  typename Value = typename Container::value_type,
  std::enable_if_t<!std::is_same< Container, std::string >::value, std::nullptr_t> = nullptr
>
std::istream& operator>> (std::istream& is, Container& v) {
  for (auto & x : v) is >> x;
  return is;
}

template < typename Container,
  typename Value = typename Container::value_type,
  std::enable_if_t<!std::is_same< Container, std::string >::value, std::nullptr_t> = nullptr
>
std::ostream& operator<< (std::ostream& os, Container const& v) {
  os << "{";
  for (auto it = v.begin(); it != v.end(); it++)
    {os << (it != v.begin() ? "," : "") << *it;}
  return os << "}";
}
