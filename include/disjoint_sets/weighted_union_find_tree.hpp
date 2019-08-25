template <typename Value, typename BinaryOp1, typename BinaryOp2>
class weighted_union_find_tree
{
  int                n;
  std::vector<int>   prt;
  std::vector<Value> wt;
  BinaryOp1          op1;
  BinaryOp2          op2;
  Value              id;

  auto op1_eq (Value& x, Value y) const {return x = op1(x, y);}
  auto op2_eq (Value& x, Value y) const {return x = op2(x, y);}
  auto inv_eq (Value& x)          const {return x = op2(id, x);}
  auto inv    (Value& x)          const {return inv_eq(x);}

public:
  weighted_union_find_tree
    (int n, BinaryOp1 op1, BinaryOp2 op2, Value id) :
    n(n), prt(n, -1), wt(n, id), op1(op1), op2(op2), id(id)
    {}

  bool is_root   (int x)        const {return prt.at(x) < 0;}
  int  size      (int x)              {return -prt.at(find(x));}
  bool same      (int x, int y)       {return find(x) == find(y);}
  auto collect   ()             const {return prt;}

  auto get       (int x)
  {
    find(x);
    return wt.at(x);
  }
  auto quiet_get (int x) const
  {
    auto ret = id;
    while(!is_root(x))
    {
      op1_eq(ret, wt.at(x));
      x = prt.at(x);
    }
    return ret;
  }

  // x - y
  auto diff      (int x, int y)
  {
    assert(same(x, y));
    return op2(get(x), get(y));
  }
  auto collect_wts ()
  {
    auto ret = std::vector<Value>(n);
    for (auto i = 0; i < n; i++)
    {
      ret.at(i) = get(i);
    }
    return ret;
  }
  auto quiet_collect_wts() const
  {
    auto ret = std::vector<Value>(n);
    for (auto i = 0; i < n; i++)
    {
      ret.at(i) = quiet_get(i);
    }
    return ret;
  }

  // Path compression.
  int  find    (int x)
  {
    if (is_root(x)) return x;
    else
    {
      auto root = find(prt.at(x));
      op1_eq(wt.at(x), wt.at(prt.at(x)));
      return prt.at(x) = root;
    }
  }

  // Returns `true` if x and y are newly connected.
  // x is the parent.
  // x - y = d
  bool unite   (int x, int y, Value d)
  {
    inv_eq(d);
    op1_eq(d, get(x));
    op2_eq(d, get(y));
    if ((x = find(x)) == (y = find(y)))
    {
      assert(op2(get(x), get(y)) == d);
      return false;
    }
    if (size(x) < size(y))
    {
      std::swap(x, y);
      inv_eq(d);
    }
    prt.at(x) += prt.at(y);
    prt.at(y) = x;
    wt.at(y) = d;
    return true;
  }
};

template <typename Value, typename BinaryOp1, typename BinaryOp2>
auto make_weighted_union_find_tree(int n, BinaryOp1 op1, BinaryOp2 op2, Value id)
{
  return weighted_union_find_tree<Value, BinaryOp1, BinaryOp2>(n, op1, op2, id);
}