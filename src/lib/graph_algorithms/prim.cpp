template <typename T>
struct prim {
  const int n;
  std::vector<std::vector<std::pair<T, int>>> grh;
  T weight_of_mst;
  prim (
      std::vector<std::vector<std::pair<T, int>>> grh
    ) :
    n(grh.size()),
    grh(grh),
    weight_of_mst(0)
    {
      std::vector<bool> ckd(n, false);
      priority_queue<
        std::pair<T, int>,
        std::vector<std::pair<T, int>>,
        greater<std::pair<T, int>>
      > que;
      que.emplace(0, 0);
      while (!que.empty()) {
        T w; int t;
        std::tie(w, t) = que.top(), que.pop();
        if (ckd[t]) continue;
        weight_of_mst += w, ckd[t] = true;
        for (auto p : grh[t]) que.push(p);
      }
    }
};