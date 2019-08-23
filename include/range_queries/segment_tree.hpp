template<typename Value, typename BinaryOp>
class segment_tree
{
    int                 n, N;
    BinaryOp            op;
    Value               id;
    std::vector<Value>  table;

    void cal (int u)
    {
      table.at(u) = op(table.at(2 * u), table.at(2 * u + 1));
    }

  public:
    segment_tree(int size, BinaryOp op, Value id, const std::vector<Value>& v):
      n     (std::pow(2, int(std::log2(2 * size - 1)))),
      N     (n * 2),
      op    (op),
      id    (id),
      table (N, id)
    {
      assert(n > 0);
      std::move(v.begin(), v.end(), table.begin() + n);
      for (int i = n - 1; i != 0; i--) cal(i);
    }

    segment_tree(int size, BinaryOp op, Value id):
      segment_tree(size, std::move(op), id, std::vector<Value>(size, id))
      {}

    auto at (int i) const -> Value
    {
      return table.at(n + i);
    }

    auto collect () const -> std::vector<Value>
    {
      auto ret = std::vector<Value>(n);
      for (auto i = 0; i < n; i++)
      {
        ret.at(i) = at(i);
      }
      return ret;
    }

    auto query (int l, int r) const -> Value
    {
      struct state {int top, left, right;};

      auto ret = id;
      std::stack<state> stk; stk.push({1, 0, n});
      while (!stk.empty())
      {
        auto now = stk.top(); stk.pop();
        if (l <= now.left && now.right <= r)
        {
          ret = op(ret, table.at(now.top));
          continue;
        }
        int mid = (now.left + now.right) / 2;
        if (l < mid) stk.push({2 * now.top,     now.left,  mid});
        if (mid < r) stk.push({2 * now.top + 1, mid, now.right});
      }
      return ret;
    }

    void update (int u, Value val)
    {
      table.at(u += n) = val;
      for (u /= 2; u != 0; u /= 2) cal(u);
    }

    void add (int u, Value val)
    {
      update(u, at(u) + val);
    }
};

template<typename Value, typename BinaryOp>
auto make_segment_tree(int size, BinaryOp op, Value vid)
{
  return segment_tree<Value, BinaryOp>(size, std::move(op), vid);
}

template<typename Value, typename BinaryOp>
auto make_segment_tree(int size, BinaryOp op, Value vid, std::vector<int> v)
{
  return segment_tree<Value, BinaryOp>(size, std::move(op), vid, std::move(v));
}