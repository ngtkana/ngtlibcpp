template <typename Value, typename BinaryOp1, typename BinaryOp2>
class weighted_quick_find
{
  int                           n;
  std::vector<int>              prt;
  std::vector<std::vector<int>> child;
  std::vector<Value>            table;
  BinaryOp1                     op1;
  BinaryOp2                     op2;
  Value                         id;

  auto& op1_eq (Value& x, Value y) const {return x = op1(x, y);}
  auto& op2_eq (Value& x, Value y) const {return x = op2(x, y);}
  auto& inv_eq (Value& x)          const {return x = op2(id, x);}

public:
  weighted_quick_find (int n, BinaryOp1 op1, BinaryOp2 op2, Value id) :
    n(n), prt(n), child(n), table(n, id), op1(op1), op2(op2), id(id)
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

  // x - y
  auto diff    (int x, int y) const
  {
    assert(same(x, y));
    return op2(table.at(x), table.at(y));
  }

  // Returns `true` if x and y are newly connected.
  // x - y = d
  bool unite   (int x, int y, Value d)
  {
    inv_eq(d);
    op1_eq(d, table.at(x));
    op2_eq(d, table.at(y));
    if ((x = find(x)) == (y = find(y))) return false;
    if (size(x) < size(y))
    {
      std::swap(x, y);
      inv_eq(d);
    }
    for (auto z : child.at(y))
    {
      prt.at(z) = x;
      op1_eq(table.at(z), d);
      child.at(x).push_back(z);
    }
    typename decltype(child)::value_type{}.swap(child.at(y));
    return true;
  }
};

template <typename Value, typename BinaryOp1, typename BinaryOp2>
auto make_weighted_quick_find(int n, BinaryOp1 op1, BinaryOp2 op2, Value id) {
  return weighted_quick_find<Value, BinaryOp1, BinaryOp2>(n, op1, op2, id);
}