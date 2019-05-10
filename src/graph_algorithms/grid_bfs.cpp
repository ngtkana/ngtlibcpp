constexpr int inf = 1 << 30;
vector<vector<int>> dst(h, vector<int>(w, inf));
queue<tuple<int, int, int>> que;
for (int i = 0; i < h; i++) {
  for (int j = 0; j < w; j++) {
    if (a[i][j]) que.emplace(0, i, j);
  }
}
while (!que.empty()) {
  int crd, cri, crj;
  tie(crd, cri, crj) = que.front(), que.pop();
  if (!chmin(dst[cri][crj], crd)) continue;
  for (int k = 0; k < 4; k++) {
    int nxd = crd + 1;
    int nxi = cri + di[k];
    int nxj = crj + dj[k];
    if (
        0 <= nxi && nxi < h &&
        0 <= nxj && nxj <= w &&
        nxd < dst[nxi][nxj]
      ) que.emplace(nxd, nxi, nxj);
  }