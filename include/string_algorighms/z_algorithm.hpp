auto make_z_array(std::string s) -> std::vector<int>
{
  if (s.empty()) return {};
  int n = s.length();
  std::vector<int> ret(n);
  ret.at(0) = n;
  int i = 1, j = 0;
  while (i < n) {
    while (i + j < n && s.at(j) == s.at(i + j)) {
      j++;
    }
    ret.at(i) = j;
    if (j == 0) {
      i++;
    }
    else {
      int k = 1;
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
auto z_search(std::string w, std::string s, char dammy = '$') -> std::vector<int> {
  if (s.empty()) return {};
  assert(!w.empty());
  int m = w.length(), n = s.length();
  assert(std::find(w.begin(), w.end(), dammy) == w.end());
  assert(std::find(s.begin(), s.end(), dammy) == s.end());
  auto long_string = w + '$' + s;
  auto z_array = make_z_array(std::move(long_string));
  std::vector<int> ret;
  for (int i = 0; i < n; i++) {
    if (z_array.at(m + 1 + i) == m) {
      ret.push_back(i);
    }
  }
  return ret;
}