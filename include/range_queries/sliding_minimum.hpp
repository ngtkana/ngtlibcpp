template < typename Value, typename Cmp = std::less< Value > >
class sliding_minimum {
    std::deque< Value > que;

    void pop_left_until(int target) {
      assert(target <= right);
      while (left < target)
        { shrink(); }
    }
    void push_right_until(int target) {
      assert(target <= n);
      while (right < target)
        { extend(); }
    }

  public:
    int                  n;
    std::vector< Value > v;
    Cmp                  cmp;
    int                  left, right;

    sliding_minimum(std::vector< Value > const& v) :
      n    (v.size()),
      v    (v),
      cmp  (Cmp()),
      left (0),
      right(0)
      {}

    auto get_left_index()  const { return left; }
    auto get_right_index() const { return right; }

    auto query_index() const
      { assert(!que.empty()); return que.front(); }
    auto query() const
      { return v.at(query_index()); }

    void shrink() {
      if (que.front() == left++)
        { que.pop_front(); }
      assert(left <= right);
    }
    void extend() {
      while (!que.empty() && !cmp(v.at(que.back()), v.at(right)))
        { que.pop_back(); }
      que.push_back(right++);
      assert(right <= n);
    }
    void slide()
      { shrink(); extend(); }
    void move(int l, int r) {
      push_right_until(r);
      pop_left_until(l);
    }
};
