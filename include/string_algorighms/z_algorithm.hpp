template < template < typename ... > class Container, typename Value >
auto make_z_array(Container< Value > const & s) -> std::vector< int > {
  if (s.empty()) return {};
  auto n = (int)s.size();
  std::vector< int > ret(n);
  ret.at(0) = n;
  auto i = 1, j = 0;
  while (i < n) {
    while (i + j < n && s.at(j) == s.at(i + j))
      { j++; }
    ret.at(i) = j;
    if (j == 0)
      { i++; }
    else {
      auto k = 1;
      while (i + k < n && k + ret.at(k) < j) {
        ret.at(i + k) = ret.at(k);
        k++;
      }
      i += k, j -= k;
    }
  }
  return ret;
}

// Returns turns all the occurence of w in s.
template < template < typename ... > class Container, typename Value >
auto z_search(Container< Value > const & w, Container< Value > const & s, Value dammy) -> std::vector<int> {
  if (s.empty()) return {};
  assert(!w.empty());
  assert(std::find(w.begin(), w.end(), dammy) == w.end());
  assert(std::find(s.begin(), s.end(), dammy) == s.end());
  auto long_string = w;
  long_string.push_back(dammy);
  long_string.insert(long_string.end(), s.begin(), s.end());
  auto z_array = make_z_array(std::move(long_string));
  int m = w.size(), n = s.size();
  std::vector<int> ret;
  for (int i = 0; i < n; i++) {
    if (z_array.at(m + 1 + i) == m)
      { ret.push_back(i); }
  }
  return ret;
}
