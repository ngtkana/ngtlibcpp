int ${1:n}, ${2:m};
std::cin >> $1 >> $2;
constexpr ${3:long long} inf = 1LL << 60;
std::vector<std::vector<$3>> adj(n, std::vector<$3>(n, inf));
for (int i = 0; i < $1; i++) adj[i][i] = 0;
for (int i = 0; i < m; i++) {
  $3 d; int s, t;
  std::cin >> s >> t >> d;
  chmin(adj[s][t], d);
}