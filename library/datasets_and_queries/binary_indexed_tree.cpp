#include <bits/stdc++.h>
using namespace std;
// begin
template <typename T>
class binary_indexed_tree {
  int sz;
  vector<T> tr;
  function<T(T, T)> o;
  function<T(T, T)> dif;
  T id;
  public:
    binary_indexed_tree (
      int n
    , function<T(T, T) > o = [](int a, int b) {return a + b;}
    , function<T(T, T) > dif = [](int a, int b) {return a - b;}
    , T id = 0
    )
    : sz(n)
    , tr(n, id)
    , o(o)
    , dif(dif)
    , id(id)
    {
    }
    T query (int l, int r) {
      assert(0 <= l && l <= r && r <= sz);
      if (l == 0) {
        r--;
        T ret = 0;
        for (; r >= 0; r &= r + 1, r--) ret = o(ret, tr[r]);
        return ret;
      }
      return dif(query(0, r), query(0, l));
    }
    void add (int i, T x) {
      for (; i < sz; i |= i + 1) tr[i] = o(tr[i], x);
    }
    void print() {
      cout << "bit: ";
      for (int i = 0; i < sz; i++) {
        cout << query(i, i + 1);
        if (i == sz - 1) break;
        cout << ' ';
      }
      cout << endl;
    }
};
// end
