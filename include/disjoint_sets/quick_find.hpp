class quick_find
{
  int                           n;
  std::vector<int>              leader;
  std::vector<std::vector<int>> members;

public:
  quick_find (int n) : n(n), leader(n), members(n)
  {
    std::iota(leader.begin(), leader.end(), 0);
    for (int i = 0; i < n; i++) {
      members.at(i) = {i};
    }
  }

  auto collect ()             const {return leader;}

  bool is_root (int x)        const {return find(x) == x;}

  int  size    (int x)        const {return members.at(x).size();}

  bool same    (int x, int y) const {return find(x) == find(y);}

  int  find    (int x)        const {return leader.at(x);}

  // Returns `true` if x and y are newly connected.
  bool unite   (int x, int y)
  {
    if ((x = find(x)) == (y = find(y))) return false;
    if (size(x) > size(y)) std::swap(x, y);
    for (auto child : members.at(x))
    {
      leader.at(child) = y;
      members.at(y).push_back(child);
    }
    decltype(members)::value_type{}.swap(members.at(x));
    return true;
  }
};