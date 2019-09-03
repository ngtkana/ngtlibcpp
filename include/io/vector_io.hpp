template <typename T>
std::istream& operator>> (std::istream& is, std::vector<T>& v) {
  for (auto & x : v) is >> x;
  return is;
}

template <typename T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& v) {
  auto n = v.size();
  os << "{";
  for (size_t i = 0; i < n; i++)
    {os << (i > 0 ? "," : "") << v.at(i);}
  return os << "}";
}