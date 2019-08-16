template <typename T>
auto compress(const T& v)
  -> std::vector<int>
{
  int n = v.size();
  auto ord = std::vector<int>(n);
  std::iota(ord.begin(), ord.end(), 0);
  std::sort(ord.begin(), ord.end(), [&](auto i, auto j)
  {
    return v.at(i) < v.at(j);
  });
  auto c = std::vector<int>(n);
  int classes = 0;
  for (auto it = ord.begin(); it != ord.end(); it++)
  {
    if (it != ord.begin() && v.at(*it) != v.at(*std::prev(it)))
    {
      classes++;
    }
    c.at(*it) = classes;
  }
  return c;
}

auto suffix_array(const std::string& s)
  -> std::vector<int>
{
  int n  = s.size();
  auto c = compress(s);
  for (int k = 1; k < n; k *= 2)
  {
    std::vector<std::pair<int, int>> pairs(n);
    for (int i = 0; i < n; i++)
    {
      pairs.at(i) = {c.at(i), c.at((i + k) % n)};
    }
    c = compress(pairs);
  }
  std::vector<int> p(n); // = c ^ {-1}
  for (int i = 0; i < n; i++)
  {
    p.at(c.at(i)) = i;
  }
  return p;
}