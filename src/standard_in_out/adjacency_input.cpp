int ${1:n}, ${2:m};
cin >> $1 >> $2;
constexpr ${3:long long} inf = 1LL << 60;
vector<vector<$3>> adj(n, vector<$3>(n, inf));
for (int i = 0; i < $1; i++) adj[i][i] = 0;
for (int i = 0; i < m; i++) {
  $3 d; int s, t;
  cin >> s >> t >> d;
  chmin(adj[s][t], d);
}