template <typename T, typename U>
std::ostream& operator<< (std::ostream& os, const std::pair<T, U>& pair)
  { return os << "(" << pair.first << "," << pair.second << ")"; }

template <typename T, typename U>
std::istream& operator>> (std::iostream& is, std::pair<T, U>& pair)
  { return is >> pair.first >> pair.second; }