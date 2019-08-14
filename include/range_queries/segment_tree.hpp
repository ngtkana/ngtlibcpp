template<typename Value, typename BinaryOp>
class segment_tree
{
  public:
    using size_type      = int;
    using value_type     = Value;
    using function_type  = BinaryOp;
    using container_type = std::vector<value_type>;

  private:
    size_type       n, N;
    function_type   op;
    value_type      id;
    container_type  table;

    void cal (size_type u)
    {
      table.at(u) = op(table.at(2 * u), table.at(2 * u + 1));
    }

  public:
    segment_tree(int size, BinaryOp op, Value id, const std::vector<Value>& v):
      n     (std::pow(2, int(std::log2(size)) + 1)),
      N     (n * 2),
      op    (op),
      id    (id),
      table (N, id)
    {
      assert(n > 0);
      std::move(v.begin(), v.end(), table.begin() + n);
      for (size_type i = n - 1; i != 0; i--) cal(i);
    }

    segment_tree(int size, BinaryOp op, Value id):
      segment_tree(size, std::move(op), id, std::vector<Value>(size, id))
      {}

    auto at (size_type i) const -> value_type
    {
      return table.at(n + i);
    }

    auto query (size_type l, size_type r) const -> value_type
    {
      struct state {size_type top, left, right;};

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
        size_type mid = (now.left + now.right) / 2;
        if (l < mid) stk.push({2 * now.top,     now.left,  mid});
        if (mid < r) stk.push({2 * now.top + 1, mid, now.right});
      }
      return ret;
    }

    void update (size_type u, value_type val)
    {
      table.at(u += n) = val;
      for (u /= 2; u != 0; u /= 2) cal(u);
    }

    void add (size_type u, value_type val)
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
