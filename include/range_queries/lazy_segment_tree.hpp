template<
  typename Value1,    typename Value2,
  typename BinaryOp1, typename BinaryOp2, typename BinaryOp3,
  typename UnaryOp1,  typename UnaryOp2
  >
class lazy_segment_tree
{
    struct node
    {
      int id, l, r;
      node (int id, int l, int r):
        id(id), l(l), r(r)
        {};

      auto size () const {return r - l;}

      auto left_child  () const
      {
        assert(size() > 1);
        return node(id * 2, l, (l + r) / 2);
      }

      auto right_child () const
      {
        assert(size() > 1);
        return node(id * 2 + 1, (l + r) / 2, r);
      }
    };

    int                 n, N;
    BinaryOp1           op1;
    BinaryOp2           op2;
    BinaryOp3           op3;
    Value1              id1;
    Value2              id2;
    UnaryOp1            expand;
    UnaryOp2            shrink;
    std::vector<Value1> table;
    std::vector<Value2> lazy;
    node                initial_node;

    auto& op1_eq (Value1& x, Value1 y) {return x = op1(x, y);}
    auto& op2_eq (Value1& x, Value2 y) {return x = op2(x, y);}
    auto& op3_eq (Value2& x, Value2 y) {return x = op3(x, y);}

    void cal (int u)
    {
      table.at(u) = op1(table.at(2 * u), table.at(2 * u + 1));
    }

    auto chain (int u) const
    {
      auto ret = std::vector<int>{};
      for (auto i = u; i > 0; i /= 2)
      {
        ret.emplace_back(i);
      }
      std::reverse(ret.begin(), ret.end());
      return ret;
    }

    auto prop (int u)
    {
      op2_eq(table.at(u), lazy.at(u));
      if (u < n)
      {
        op3_eq(lazy.at(2 * u),     shrink(lazy.at(u)));
        op3_eq(lazy.at(2 * u + 1), shrink(lazy.at(u)));
      }
      lazy.at(u)     = id2;
      return table.at(u);
    }

    auto query_base (int l, int r, Value2 val, const node& now)
    {
      prop(now.id);
      if (now.r <= l || r <= now.l) return id1;
      else if (l <= now.l && now.r <= r)
      {
        op3_eq(lazy.at(now.id), val);
        return prop(now.id);
      }
      else
      {
        auto ret =op1(
          query_base(l, r, shrink(val), now.left_child()),
          query_base(l, r, shrink(val), now.right_child())
        );
        cal(now.id);
        return ret;
      }
    }

  public:
    lazy_segment_tree
    (
      int size,
      BinaryOp1  op1,
      BinaryOp2  op2,
      BinaryOp3  op3,
      Value1     id1,
      Value2     id2,
      UnaryOp1   expand,
      UnaryOp2   shrink
    ):
      n (std::pow(2, int(std::log2(size)) + 1)), N(n * 2),
      op1(std::move(op1)), op2(std::move(op2)), op3(std::move(op3)),
      id1(id1), id2(id2),
      expand(std::move(expand)), shrink(std::move(shrink)),
      table(N, id1), lazy(N, id2),
      initial_node(1, 0, n)
      {
        std::mt19937 mt(std::random_device{}());
        std::uniform_int_distribution<int> dist(-1'000'000, 1'000'000);
        for (int i = 0; i < 20; i++) {
          Value1 ex1 = dist(mt), ex1_ = dist(mt);
          Value2 ex2 = dist(mt);
          assert(op1(ex1, id1)       == ex1);
          assert(op2(ex1, id2)       == ex1);
          assert(op3(ex2, id2)       == ex2);
          assert(shrink(expand(ex2)) == ex2);
          assert(op2(op1(ex1, ex1_), expand(ex2)) == op1(op2(ex1, ex2), op2(ex1_, ex2)));
        }
      }

    void build (const Value1 x)
    {
      std::fill(table.begin(), table.end(), x);
    }

    void build (const std::vector<Value1>& v)
    {
      assert(int(v.size()) <= n);
      std::move(v.begin(), v.end(), table.begin() + n);
      for (int i = n - 1; i >= 0; i--) cal(i);
    }

    void act (int l, int r, Value2 val)
    {
      for (int i = 1; i < n; i *= 2) {
        val = expand(val);
      }
      query_base(l, r, val, initial_node);
    }

    auto query (int l, int r)
    {
      return query_base(l, r, id2, initial_node);
    }

    auto quiet_at (int i) const
    {
      i += n;
      auto actor = id2;
      for (auto j : chain(i))
      {
        actor = shrink(actor);
        actor = op3(actor, lazy.at(j));
      }
      return op2(table.at(i), actor);
    }

    auto quiet_collect () const
    {
      auto ret = std::vector<Value1>(n);
      for (auto i = 0; i < n; i++)
      {
        ret.at(i) = quiet_at(i);
      }
      return ret;
    }

    auto at (int i)
    {
      i += n;
      for (auto j : chain(i))
      {
        prop(j);
      }
      return table.at(i);
    }

    auto collect ()
    {
      for (int i = 0; i < N; i++)
      {
        prop(i);
      }
      auto ret = std::vector<Value1>(n);
      for (auto i = 0; i < n; i++)
      {
        ret.at(i) = table.at(i + n);
      }
      return ret;
    }
};

template<
  typename Value1,    typename Value2,
  typename BinaryOp1, typename BinaryOp2, typename BinaryOp3,
  typename UnaryOp1,  typename UnaryOp2
  >
auto make_lazy_segment_tree
(
  int        size,
  BinaryOp1  op1,
  BinaryOp2  op2,
  BinaryOp3  op3,
  Value1     id1,
  Value2     id2,
  UnaryOp1   expand,
  UnaryOp2   shrink
)
{
  return lazy_segment_tree<
    Value1,    Value2,
    BinaryOp1, BinaryOp2, BinaryOp3,
    UnaryOp1,  UnaryOp2
    >
    (
      size, std::move(op1), std::move(op2), std::move(op3),
      id1, id2, std::move(expand), std::move(shrink)
    );
}


template<
  typename Value1,    typename Value2,
  typename BinaryOp1, typename BinaryOp2, typename BinaryOp3
  >
auto make_lazy_segment_tree
(
  int        size,
  BinaryOp1  op1,
  BinaryOp2  op2,
  BinaryOp3  op3,
  Value1     id1,
  Value2     id2
)
{
  auto f = [](auto x){return x;};
  return make_lazy_segment_tree
    (
      size, std::move(op1), std::move(op2), std::move(op3),
      id1, id2, std::move(f), std::move(f)
    );
}