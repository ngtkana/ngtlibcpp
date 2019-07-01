template <typename T, class Compare = less<T>>
class slide_minimum {
  public:
  const std::vector<T> a;
  Compare cmp;
  deque<int> que;
  int l, r;
    slide_minimum(
        const std::vector<T>& a
      ) :
      a(a), cmp(Compare()), l(0), r(0)
      {
      }
    inline void luc () {
      if (que.front() == l++) {
        que.pop_front();
      }
    }
    inline void ruc () {
      while (!que.empty() && !cmp(a[que.back()], a[r])) {
        que.pop_back();
      }
      que.push_back(r++);
    }
    inline auto query () const -> T {
      assert(!que.empty());
      return a[que.front()];
    }
    inline auto query_index () const -> int {
      assert(!que.empty());
      return que.front();
    }
};