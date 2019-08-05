template<typename T, typename F, std::enable_if_t<
  std::is_same<std::result_of_t<F(T, T)>, T>::value,
  std::nullptr_t
> = nullptr>
class segment_tree {
    using vec = std::vector<T>;
    size_t ht, n, N;
    F o; T id; vec tab;
    void cal (size_t u) {tab.at(u) = o(tab.at(2 * u), tab.at(2 * u + 1));}

  public:
    using value_type    = T;
    using function_type = F;
    segment_tree(
        size_t size,
        F      merge_function,
        T      id,
        vec    v
      ) :
      ht(std::log2(size) + 2), n(std::pow(2, ht - 1)), N(n * 2),
      o(merge_function), id (id), tab(N)
      {
        assert(n > 0);
        v.resize(n, id);
        std::copy(v.begin(), v.end(), tab.begin() + n);
        for (size_t i = n - 1; i != 0; i--) cal(i);
      }
    segment_tree(
        size_t size,
        F      merge_function,
        T      id
      ) :
      segment_tree(size, std::move(merge_function), id, vec(size, id)){}

    // Change a value at the leaf.
    void update (size_t u, T val) {
      tab.at(u += n) = val;
      for (u /= 2; u != 0; u /= 2) cal(u);
    }
    // Range-something query at [l, r[.
    auto query (size_t l, size_t r) const -> T {
      struct state {size_t top, left, right;};
      auto ret = id;
      std::stack<state> stk; stk.push({1, 0, n});
      while (!stk.empty()) {
        auto now = stk.top(); stk.pop();
        if (l <= now.left && now.right <= r) {
          ret = o(ret, tab.at(now.top));
          continue;
        }
        size_t mid = (now.left + now.right) / 2;
        if (l < mid) stk.push({2 * now.top,     now.left,  mid});
        if (mid < r) stk.push({2 * now.top + 1, mid, now.right});
      }
      return ret;
    }
};
template<typename T, typename F, typename... Args>
auto make_segment_tree (
    size_t  size,
    F       merge_function,
    Args... args
  )
  {
    return segment_tree<T, F>(
      size, std::move(merge_function), std::forward<Args>(args)...);
  }