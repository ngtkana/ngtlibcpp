constexpr ${1:long long} inf = ${2:1LL << 60};
vector<$1> dst(n, inf);
priority_queue<
  pair<$1, int>,
  vector<pair<$1, int>>,
  greater<pair<$1, int>>
> que;
que.emplace(0, ${3:r});
while (!que.empty()) {
  $1 crd; int crr;
  tie(crd, crr) = que.top(), que.pop();
  if (!chmin(dst[crr], crd)) continue;
  for (auto e : grh[crr]) {
    $1 w; int nxt; tie(w, nxt) = e;
    $1 nxd = crd + w;
    if (dst[nxt] > nxd) que.emplace(nxd, nxt);
  }
}