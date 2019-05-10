template <typename T>
struct prim {
  const int n;
  vector<vector<pair<T, int>>> grh;
  T weight_of_mst;
  prim (
      vector<vector<pair<T, int>>> grh
    ) :
    n(grh.size()),
    grh(grh),
    weight_of_mst(0)
    {
      vector<bool> ckd(n, false);
      priority_queue<
        pair<T, int>,
        vector<pair<T, int>>,
        greater<pair<T, int>>
      > que;
      que.emplace(0, 0);
      while (!que.empty()) {
        T w; int t;
        tie(w, t) = que.top(), que.pop();
        if (ckd[t]) continue;
        weight_of_mst += w, ckd[t] = true;
        for (auto p : grh[t]) que.push(p);
      }
    }
};