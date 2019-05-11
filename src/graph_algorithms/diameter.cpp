template<typename T>
class calculate_diameter {
  const int n;
  const vector<vector<pair<T, int>>>& grh;
  int max_dpt;
  int far_0, far_1;

    void dfs (
        int crr,
        int prt,
        T dpt,
        int& far
      ) {
        if (chmax(max_dpt, dpt)) far = crr;
        for (auto const& e : grh[crr]) {
          T w; int nxt; tie(w, nxt) = e;
          if (nxt == prt) continue;
          dfs(nxt, crr, dpt + w, far);
        }
      }

  public:
    calculate_diameter(
        vector<vector<pair<T, int>>>& grh
      ) :
      n(grh.size()),
      grh(grh),
      max_dpt(0),
      far_0(0), far_1(0)
      {
        dfs(0, 0, 0, far_0);
        dfs(far_0, far_0, 0, far_1);
      }

    T diameter () const {return max_dpt;}
    auto extremal () const -> pair<int, int> {return {min(far_0, far_1), max(far_0, far_1)};}
};