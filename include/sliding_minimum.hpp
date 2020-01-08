template < typename Value, typename Cmp = std::less< Value > >
class sliding_minimum {
    std::deque< Value > que;
    void pop_to(int target) {
      assert(target <= right);
      while (left < target)
        { shrink(); }
    }
    void push_to(int target) {
      assert(target <= n);
      while (right < target)
        { extend(); }
    }
  public:
    int n, left, right;
    std::vector< Value > v;
    Cmp                  cmp;
    sliding_minimum(std::vector< Value > const& v, Cmp const & cmp) :
      n(v.size()), left(0), right(0), v(v), cmp(cmp)
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
    void advance_to(int l, int r)
      { push_to(r); pop_to(l); }
};
template < typename Value, typename Cmp = std::less< Value > >
auto make_sliding_minimum(std::vector< Value > const& v, Cmp const & cmp)
  { return sliding_minimum< Value, Cmp >(v, cmp); }
