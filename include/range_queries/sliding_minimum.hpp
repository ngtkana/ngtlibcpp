template <typename T, typename Compare = std::less<T>>
class sliding_minimum {
public:
  using size_type     = int;
  using position_type = int;
  using value_type    = T;
  using sequence_type = std::vector<T>;
  using deque_type    = std::deque<T>;
  using compare_type  = Compare;

private:
  deque_type que;

public:
  size_type     n;
  sequence_type v;
  compare_type  cmp;
  position_type left, right;

  sliding_minimum
  (
    sequence_type const& v
  ) :
  n    (v.size()),
  v    (v),
  cmp  (Compare()),
  left (0),
  right(0)
  {}

  auto get_left_index() const -> position_type
  {
    return left;
  }

  auto get_right_index() const -> position_type
  {
    return right;
  }

  auto query_index() const -> position_type
  {
    assert(!que.empty());
    return que.front();
  }

  auto query() const -> value_type
  {
    return v.at(query_index());
  }

  void pop_left()
  {
    if (que.front() == left++) {
      que.pop_front();
    }
    assert(left <= right);
  }

  void push_right()
  {
    while (!que.empty() && !cmp(v.at(que.back()), v.at(right))) {
      que.pop_back();
    }
    que.push_back(right++);
    assert(right <= n);
  }

  void slide()
  {
    pop_left();
    push_right();
  }

  void pop_left_until(int target)
  {
    assert(target <= right);
    while (left < target) pop_left();
  }

  void push_right_until(int target)
  {
    assert(target <= n);
    while (right < target) push_right();
  }

  void advance_until(int l, int r)
  {
    push_right_until(r);
    pop_left_until(l);
  }
};