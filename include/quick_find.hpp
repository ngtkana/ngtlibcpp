class quick_find
{
  int                           n;
  std::vector<int>              prt;
  std::vector<std::vector<int>> child;

public:
  quick_find (int n) : n(n), prt(n), child(n)
  {
    std::iota(prt.begin(), prt.end(), 0);
    for (int i = 0; i < n; i++) {
      child.at(i) = {i};
    }
  }

  auto collect ()             const {return prt;}
  bool is_root (int x)        const {return find(x) == x;}
  int  size    (int x)        const {return child.at(prt.at(x)).size();}
  bool same    (int x, int y) const {return find(x) == find(y);}
  int  find    (int x)        const {return prt.at(x);}

  // Returns `true` if x and y are newly connected.
  bool unite   (int x, int y)
  {
    if ((x = find(x)) == (y = find(y))) return false;
    if (size(x) > size(y)) std::swap(x, y);
    for (auto z : child.at(x))
    {
      prt.at(z) = y;
      child.at(y).push_back(z);
    }
    decltype(child)::value_type{}.swap(child.at(x));
    return true;
  }
};