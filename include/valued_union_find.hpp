
template <typename Value, typename BinaryOp>
class valued_union_find
{
  int                n;
  std::vector<Value> table;
  std::vector<int>   prt;
  BinaryOp           op;
  Value              id;

public:
  valued_union_find (int n, BinaryOp op, Value id, Value init) :
    n(n), table(n, init), prt(n, -1), op(op), id(id)
    {}

  bool is_root (int x)        const {return prt.at(x) < 0;}
  int  size    (int x)        const {return -prt.at(find(x));}
  bool same    (int x, int y) const {return find(x) == find(y);}
  int  find    (int x)        const
  {
    while (!is_root(x)) x = prt.at(x);
    return x;
  }
  auto collect ()             const {return prt;}

  // Returns `true` if x and y are newly connected.
  // y becomes the partent.
  bool unite   (int x, int y)
  {
    if ((x = find(x)) == (y = find(y))) return false;
    if (size(x) > size(y)) std::swap(x, y);
    prt.at(y) += prt.at(x);
    prt.at(x) = y;
    table.at(y) = op(table.at(y), table.at(x));
    table.at(x) = id;
    return true;
  }

  auto get     (int x)        const {return table.at(find(x));}
  auto collect_vals ()        const
  {
    std::vector<Value> ret(n);
    for (auto i = 0; i < n; i++)
    {
      ret.at(i) = get(i);
    }
    return ret;
  }
  void set     (int x, Value val)    {table.at(find(x)) = val;}
  void add     (int x, Value val)    {set(x, get(x) + val);}
};

template <typename Value, typename BinaryOp>
auto make_valued_union_find(int n, BinaryOp op, Value id, Value init)
{
  return valued_union_find<Value, BinaryOp>(n, op, id, init);
}