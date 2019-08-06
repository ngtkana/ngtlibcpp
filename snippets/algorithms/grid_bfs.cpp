std::vector<std::vector<${1:long long}>> dst(h, std::vector<$1>(w, ${4:-1}));
queue<std::pair<int, int>> que;
dst[${2:si}][${3:sj}] = 0, que.emplace($2, $3);
while (!que.empty()) {
  int cri, crj;
  std::tie(cri, crj) = que.front(), que.pop();
  for (int k = 0; k < 4; k++) {
    int nxi = cri + di[k];
    int nxj = crj + dj[k];
    if (
        0 <= nxi && nxi < h &&
        0 <= nxj && nxj <= w &&
        dst[nxi][nxj] == $4 &&
        !grd[nxi][nxj]
      ) dst[nxi][nxj] = dst[cri][crj] + 1, que.emplace(nxi, nxj);
  }
}