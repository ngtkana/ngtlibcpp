template <typename T>
class disjoint_sparse_table {
  const int n, ht;
  const vector<int> msb;
  const function<T(T, T)> o;
  const vector<vector<T>> tab;
  public:
    disjoint_sparse_table (
        const vector<T> a,
        const function<T(T, T)> o
      ) :
      n(a.size()),
      ht([&](){
          int ret = 1;
          for (int b = 2; b < n; b <<= 1) ret++;
          return ret;
        }()),
      msb([&](){
          int N = 1 << ht;
          auto ret = vector<int>(N, 0); ret[0] = -1;
          for (int i = 2; i < N; i++) ret[i] = ret[i >> 1] + 1;
          return ret;
        }()),
      o(o),
      tab([&](){
          auto ret = vector<vector<T>>(ht, a);
          for (int i = 1; i < ht; i++) {
            int p = 1 << i; int P = p << 1;
            for (int s = 0; s < n; s += P) {
              int t = min(s + p, n);
              for (int j = t - 2; j >= s; j--) ret[i][j] = o(a[j], ret[i][j + 1]);
              for (int j = t + 1; j < min(s + P, n); j++) ret[i][j] = o(ret[i][j - 1], a[j]);
            }
          }
          return ret;
        }())
      {
      }
    auto query (
        int l,
        int r
      ) -> T
      {
        assert(l <= --r);
        int m = msb[l ^ r];
        return m == -1 ? tab[0][l] : o(tab[m][l], tab[m][r]);
      }
};