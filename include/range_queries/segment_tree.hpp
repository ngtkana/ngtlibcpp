template<
  typename T, typename F,
  std::enable_if_t<
    std::is_same<std::result_of_t<F(T, T)>, T>::value,
    std::nullptr_t
  > = nullptr>
class segment_tree
{
public:
  using size_type     = int;
  using value_type    = T;
  using function_type = F;
  using container_type = std::vector<T>;

private:
  size_type       n, N;
  function_type   o;
  value_type      id;
  container_type  tab;

  void cal (size_type u)
  {
    tab.at(u) = o(tab.at(2 * u), tab.at(2 * u + 1));
  }

public:
  segment_tree(
    size_type      size,
    function_type  merge_function,
    value_type     id,
    container_type v
  ) :
    n   (std::pow(2, int(std::log2(size)) + 1)),
    N   (n * 2),
    o   (merge_function),
    id  (id),
    tab (N)
  {
    assert(n > 0);
    v.resize(n, id);
    std::move(v.begin(), v.end(), tab.begin() + n);
    for (size_type i = n - 1; i != 0; i--) cal(i);
  }

  segment_tree(
    size_type      size,
    function_type  merge_function,
    value_type     id
  ) :
    segment_tree(
      size,
      std::move(merge_function),
      id,
      container_type(size, id)
    )
  {}

  auto operator[] (size_type i) const -> value_type
  {
    assert(0 <= i && i < n);
    return query(i, i + 1);
  }

  auto at (size_type i) const -> value_type
  {
    return operator[](i);
  }

  // Range-something query at [l, r[.
  auto query (size_type l, size_type r) const -> value_type
  {
    struct state {
      size_type top;
      size_type left;
      size_type right;
    };
    auto ret = id;
    std::stack<state> stk; stk.push({1, 0, n});
    while (!stk.empty()) {
      auto now = stk.top(); stk.pop();
      if (l <= now.left && now.right <= r) {
        ret = o(ret, tab.at(now.top));
        continue;
      }
      size_type mid = (now.left + now.right) / 2;
      if (l < mid) stk.push({2 * now.top,     now.left,  mid});
      if (mid < r) stk.push({2 * now.top + 1, mid, now.right});
    }
    return ret;
  }

  // Change a value at the leaf.
  void update (size_type u, value_type val)
  {
    tab.at(u += n) = val;
    for (u /= 2; u != 0; u /= 2) cal(u);
  }
};

template<typename T, typename F>
auto make_segment_tree(
  int size,
  F   merge_function,
  T   id
)
{
  return segment_tree<T, F>
  (
    size,
    std::move(merge_function),
    id
  );
}

template<typename T, typename F>
auto make_segment_tree(
  int              size,
  F                merge_function,
  T                id,
  std::vector<int> v
)
{
  return segment_tree<T, F>
  (
    size,
    std::move(merge_function),
    id,
    std::move(v)
  );
}