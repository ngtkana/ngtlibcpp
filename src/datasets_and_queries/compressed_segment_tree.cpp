template< typename T >
class segment_tree {
  const vector<int> coord;
  const map<int, int> mp;
  const int sz;
  const int Sz;
  vector<T> seg;
  const function<T(T, T)> o;
  const T id;

  public:
    segment_tree (
        const vector<int> coord,
        const function<T(T, T)> o,
        const T id
      ) :
      coord([&](){
          vector<int> v = coord;
          int p = 1;
          for (; p < (int)v.size(); p <<= 1) {}
          v.resize(p, (int)((1LL << 31) - 1));
          return v;
        }()),
      mp([&](){
          map<int, int> m;
          int i = 0;
          for (auto const& e : coord) {
            m[e] = i++;
          }
          return m;
        }()),
      sz(coord.size()),
      Sz(sz << 1),
      seg(Sz, id),
      o(o),
      id(id)
      {
      }

    void update (int k, const T& x) {
      auto it = mp.find(k);
      assert(it != mp.end());
      k = it->second;
      k += sz;
      seg[k] = x;
      while(k >>= 1) {
        seg[k] = o(seg[2 * k], seg[2 * k + 1]);
      }
    }
    void add (int k, const T& x) {
      update(k, x + at(k));
    }
    T query (int l, int r) {
      l = lower_bound(coord.begin(), coord.end(), l) - coord.begin();
      r = lower_bound(coord.begin(), coord.end(), r) - coord.begin();
      T L = id, R = id;
      for(l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
        if(l & 1) L = o(L, seg[l++]);
        if(r & 1) R = o(seg[--r], R);
      }
      return o(L, R);
    }
    T at (int k) const {
      auto it = mp.find(k);
      assert(it != mp.end());
      return seg[it->second + sz];
    }
};