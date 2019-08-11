template <typename T, typename Add, typename Sub>
class binary_indexed_tree
{
public:
  using size_type         = int;
  using value_type        = T;
  using add_function_type = Add;
  using sub_function_type = Sub;
  using container_type    = std::vector<T>;

private:
  size_type         n;
  add_function_type add_function;
  sub_function_type sub_function;
  value_type        id;
  container_type    table;

public:
  binary_indexed_tree
  (
    size_type         size,
    add_function_type add_function,
    sub_function_type sub_function,
    value_type        id,
    container_type    v
  ) :
  n            (std::pow(2, int(std::log2(size)) + 1)),
  add_function (std::move(add_function)),
  sub_function (std::move(sub_function)),
  id           (id),
  table        (n, id)
  {}

  binary_indexed_tree(
    size_type         size,
    add_function_type add_function,
    sub_function_type sub_function,
    value_type        id
  ) :
    binary_indexed_tree(
      size,
      std::move(add_function),
      std::move(sub_function),
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

  // Returns the sum over [0, k[.
  auto cumulative_sum(size_type k) const -> value_type
  {
    static_assert(std::is_same<size_type, int>::value);
    assert(0 <= k && k <= n);
    value_type ret = id;
    for (k--; k >= 0; k &= k + 1, k--) {
      ret = add_function(ret, table.at(k));
    };
    return ret;
  }

  // Return the sum over [l, r[.
  auto query (size_type l, size_type r) const -> value_type
  {
    assert(0 <= l && l <= r && r <= n);
    return sub_function(cumulative_sum(r), cumulative_sum(l));
  }


  void add (size_type i, value_type x)
  {
    assert(0 <= i && i < n);
    for (; i < n; i |= i + 1) {
      table.at(i) = add_function(table.at(i), x);
    }
  }

  void update (size_type i, value_type x)
  {
    add(i, sub_function(x, at(i)));
  }
};

template<typename T, typename Add, typename Sub>
auto make_binary_indexed_tree(
  int size,
  Add add_function,
  Sub sub_function,
  T   id
)
{
  return binary_indexed_tree<T, Add, Sub>
  (
    size,
    std::move(add_function),
    std::move(sub_function),
    id
  );
}

template<typename T, typename Add, typename Sub>
auto make_binary_indexed_tree
(
  int            size,
  Add            add_function,
  Sub            sub_function,
  T              id,
  std::vector<T> v
)
{
  return binary_indexed_tree<T, Add, Sub>
  (
    size,
    std::move(add_function),
    std::move(sub_function),
    id,
    std::move(v)
  );
}