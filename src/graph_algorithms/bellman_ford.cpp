constexpr ${3:long long} inf = ${4:1LL << 60};
vector<long long> dst(${1:n}, inf);
dst[r] = 0;
int q = $1;
bool flg;
while (q--) {
  flg = false;
  for (auto const& e : edg) {
    $3 d; int s, t; tie(d, s, t) = e;
    if (dst[s] == inf) continue;
    if (chmin(dst[t], dst[s] + d)) flg = true;
  }
}
assert(!flg);