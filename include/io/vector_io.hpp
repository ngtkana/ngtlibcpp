template <typename T>
std::istream& operator>> (std::istream& is, std::vector<T>& v)
{
  for (auto & x : v) is >> x;
  return is;
}