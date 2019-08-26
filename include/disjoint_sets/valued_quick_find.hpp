template <typename Value, typename BinaryOp>
class valued_quick_find
{
  int                           n;
  std::vector<int>              prt;
  std::vector<std::vector<int>> child;
  std::vector<Value>            table;
  BinaryOp                      op;
  Value                         id;

  auto& op_eq (Value& x, Value y) const {return x = op(x, y);}

public:
  valued_quick_find (int n, BinaryOp op, Value id, Value init) :
    n(n), prt(n), child(n), table(n, init), op(op), id(id)
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
  auto get     (int x)        const {return table.at(find(x));}
  void set     (int x, Value val)   {table.at(find(x)) = val;}
  void add     (int x, Value val)   {set(x, get(x) + val);}
  auto collect_vals()         const
  {
    auto ret = std::vector<Value>(n);
    for (auto i = 0; i < n; i++)
    {
      ret.at(i) = get(i);
    }
    return ret;
  }

  // Returns `true` if x and y are newly connected.
  bool unite   (int x, int y)
  {
    if ((x = find(x)) == (y = find(y))) return false;
    if (size(x) < size(y)) std::swap(x, y);
    for (auto z : child.at(y))
    {
      prt.at(z) = x;
      child.at(x).push_back(z);
    }
    op_eq(table.at(x), table.at(y));
    table.at(y) = id;
    typename decltype(child)::value_type{}.swap(child.at(y));
    return true;
  }
};

template <typename Value, typename BinaryOp, typename BinaryOp2>
auto make_valued_quick_find(int n, BinaryOp op, Value id) {
  return valued_quick_find<Value, BinaryOp>(n, op, id);
}