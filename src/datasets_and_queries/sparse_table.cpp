template <typename T>
class sparse_table {
  const int n, ht;
  const std::vector<int> msb;
  const std::function<T(T, T)> o;
  const std::vector<std::vector<T>> tab;
  public:
    sparse_table (
        std::vector<T> a,
        std::function<T(T, T)> o
      ) :
      n(a.size()),
      ht([&](){
          int ret = 1;
          for (int b = 2; b < n; b <<= 1) ret++;
          return ret;
        }()),
      msb([&](){
          int N = 1 << ht;
          auto ret = std::vector<int>(N, 0); ret[0] = -1;
          for (int i = 2; i < N; i++) ret[i] = ret[i >> 1] + 1;
          return ret;
        }()),
      o(o),
      tab([&](){
          auto ret = std::vector<std::vector<T>>(ht, a);
          for (int i = 1, p = 1; i < ht; i++, p <<= 1) {
            for (int j = 0; j < n; j++) {
              ret[i][j] = o(ret[i - 1][j], ret[i - 1][min(j + p, n - 1)]);
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
        assert(0 <= l && l < r && r <= n);
        int i = msb[r - l];
        return o(tab[i][l], tab[i][r - (1 << i)]);
      }
};