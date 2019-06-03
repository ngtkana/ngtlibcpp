int ${1:n}, ${2:m};
cin >> $1 >> $2;
vector<tuple<${3:long long}, int, int>> edg;
for (int i = 0; i < $2; i++) {
  $3 d;
  int s, t;
  cin >> s >> t >> d;
  edg.emplace_back(d, ${4:--}s, $4t);
}