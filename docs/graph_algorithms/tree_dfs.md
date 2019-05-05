# tree_dfs
```cpp
const int infty = (int)((1LL << 31) - 1);
struct lazy_segment_tree {
  public:
    int n, N;
    vector<int> tr, lz, lzf;
    lazy_segment_tree (vector<int> v) {
      n = v.size();
      N = 1;
      while (N < n) N <<= 1;
      tr.resize(2 * N, infty);
      lz.resize(2 * N);
      lzf.resize(2 * N, false);
      for (int i = 0; i < n; i++) tr[N + i] = v[i];
      for (int i = N - 1; i >= 1; i--) tr[i] = min(tr[2 * i], tr[2 * i + 1]);
    }
    inline void pg (int k, int L, int R) {
      if (lzf[k]) {
        tr[k] = lz[k];
        if (k < N) {
          lz[2 * k] = lz[2 * k + 1] = lz[k];
          lzf[2 * k] = lzf[2 * k + 1] = true;
        }
        lzf[k] = false;
      }
    }
    void update (int l, int r, int x, int k = 1, int L = 0, int R = -1) {
      if (R == -1) R = N;
      pg(k, L, R);
      if (r <= L || R <= l) {
        return;
      } else if (l <= L && R <= r) {
        lz[k] = x;
        lzf[k] = true;
        pg(k, L, R);
      } else {
        int C = (L + R) >> 1;
        update(l, r, x, 2 * k, L, C);
        update(l, r, x, 2 * k + 1, C, R);
        tr[k] = min(tr[2 * k], tr[2 * k + 1]);
      }
    }
    int getMin (int l, int r, int k = 1, int L = 0, int R = -1) {
       if (R == -1) R = N;
      pg(k, L, R);
      if (r <= L || R <= l) {
        return infty;
      } else if (l <= L && R <= r) {
        return tr[k];
      } else {
        int C = (L + R) >> 1;
        return min(getMin(l, r, 2 * k, L, C), getMin(l, r, 2 * k + 1, C, R));
      }
    }
};
```
