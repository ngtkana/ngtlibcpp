int ${1:n}, ${2:m};
cin >> $1 >> $2;
vector<tuple<${3:long long}, int, int>> edg($2);
for (int i = 0; i < m; i++) {
  $3 d;
  int s, t;
  cin >> s >> t >> d;
  edg[i] = decltype(edg)::value_type(d, ${4:--}s, $4t);
}