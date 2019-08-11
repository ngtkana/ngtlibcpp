class union_find_tree
{
  int n;
  std::vector<int> prt;

public:
  union_find_tree (int n) : n(n), prt(n, -1){}

  bool is_root (int x)        const {return prt.at(x) < 0;}

  int  size    (int x)        const {return -prt.at(find(x));}

  bool is_equiv(int x, int y) const {return find(x) == find(y);}

  int  find    (int x)        const {
    while (!is_root(x)) x = prt.at(x);
    return x;
  }

  // Returns `true` if x and y are newly connected.
  // The smaller one x becomes a child of the larger one y.
  bool unite   (int x, int y) {
    if ((x = find(x)) == (y = find(y))) return false;
    if (size(x) > size(y)) std::swap(x, y);
    prt.at(y) += prt.at(x);
    prt.at(x) = y;
    return true;
  }
};