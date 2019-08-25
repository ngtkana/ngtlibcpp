template <typename T>
class weighted_union_find_tree
{
  int n;
  std::vector<int> prt;
  std::vector<T>   wt;

public:
  weighted_union_find_tree(int n) : n(n), prt(n, -1), wt(n, 0){}

  bool is_root (int x)        const {return prt.at(x) < 0;}

  int  size    (int x)        {return -prt.at(find(x));}

  bool same(int x, int y) {return find(x) == find(y);}

  T    weight  (int x)        {return wt.at(find(x));}

  T    diff    (int x, int y) {return weight(x) == weight(y);}

  // Path compression.
  // Cannot be inline.
  int  find    (int x)
  {
    if (is_root(x)) return x;
    else
    {
      auto root = find(prt.at(x));
      wt.at(x) += wt.at(prt.at(x));
      return prt.at(x) = root;
    }
  }

  // Returns `true` if x and y are newly connected.
  // The smaller one x becomes a child of the larger one y.
  bool unite   (int x, int y, T d)
  {
    d -= wt.at(x);
    d += wt.at(y);
    if ((x = find(x)) == (y = find(y))) return false;
    if (size(x) > size(y))
    {
      std::swap(x, y);
      d = -d;
    }
    prt.at(y) += prt.at(x);
    prt.at(x) = y;
    return true;
  }
};
