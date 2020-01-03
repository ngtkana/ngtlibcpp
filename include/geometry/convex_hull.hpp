auto convex_hull(std::vector<std::pair<int,int>> pts) {
  auto upper_hull = [&] (auto&& pts) -> std::vector<std::pair<int,int>>{
    std::vector<std::pair<int,int>> ans;
    for (auto&& p: pts) {
      int x2,y2; std::tie(x2,y2) = p;
      [&] {
        if (ans.empty()) return;
        while (ans.back().first == x2) {
          ans.pop_back();
          if (ans.empty()) return;
        }
        if (ans.size() == 1u) return;

        int x1,y1; std::tie(x1,y1) = ans.back();
        int x0,y0; std::tie(x0,y0) = *(ans.end()-2);
        int a = x1 - x0, b = y1 - y0;
        int c = x2 - x0, d = y2 - y0;
        int det = a*d-b*c;
        if (0 <= det) ans.pop_back();
      }();
      ans.emplace_back(x2,y2);
    }
    return ans;
  };

  std::sort(pts.begin(), pts.end());
  auto ans = upper_hull(pts);
  for (auto&& p : pts) {
    int x,y; std::tie(x,y) = p;
    p = {-x,-y};
  }

  std::reverse(pts.begin(), pts.end());
  auto lwr = upper_hull(pts);
  for (auto&& p : lwr) {
    int x,y; std::tie(x,y) = p;
    p = {-x,-y};
  }

  if (ans.back()==lwr.front()) ans.pop_back();
  ans.insert(ans.end(),all(lwr));
  if (ans.back()==ans.front()) ans.pop_back();
  return ans;
}